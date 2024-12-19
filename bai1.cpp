#include <iostream>
using namespace std;

struct NODE {
    int chapter;     // Thứ tự chương
    int page;        // Số trang
    int section;     // Số phần
    int subsection;  // Số tiểu mục
    NODE* left; 
    NODE* right;

    NODE(int c, int p, int s, int subs)
        : chapter(c), page(p), section(s), subsection(subs), left(nullptr), right(nullptr) {}
};

// Kiểm tra cây rỗng
bool IS_EMPTY(NODE* root) {
    return root == nullptr;
}

// Hàm tạo node mới
NODE* MAKE_NODE(int c, int p, int s, int subs) {
    return new NODE(c, p, s, subs);
}

// Hàm thêm node vào cây
NODE* INSERT(NODE* root, int c, int p, int s, int subs) {
    if (IS_EMPTY(root)) {
        return MAKE_NODE(c, p, s, subs);
    }
    if (c <= root->chapter) {
        root->left = INSERT(root->left, c, p, s, subs);
    } else {
        root->right = INSERT(root->right, c, p, s, subs);
    }
    return root;
}

// Hàm đếm số chương
int NUM_OF_CHAP(NODE* root) {
    if (IS_EMPTY(root)) return 0;
    return 1 + NUM_OF_CHAP(root->left) + NUM_OF_CHAP(root->right);
}

// Hàm tìm chương dài nhất (dựa vào số trang)
NODE* MAX_LEN(NODE* root, int& maxPages) {
    if (IS_EMPTY(root)) return nullptr;

    NODE* longest = root;
    int leftMaxPages = 0, rightMaxPages = 0;

    NODE* leftLongest = MAX_LEN(root->left, leftMaxPages);
    NODE* rightLongest = MAX_LEN(root->right, rightMaxPages);

    if (leftLongest && leftMaxPages > maxPages) {
        maxPages = leftMaxPages;
        longest = leftLongest;
    }
    if (rightLongest && rightMaxPages > maxPages) {
        maxPages = rightMaxPages;
        longest = rightLongest;
    }
    if (root->page > maxPages) {
        maxPages = root->page;
        longest = root;
    }
    return longest;
}

// Hàm tìm kiếm node
NODE* FIND(NODE* root, int chapter) {
    if (IS_EMPTY(root)) return nullptr;
    if (chapter == root->chapter) return root;
    if (chapter < root->chapter) return FIND(root->left, chapter);
    return FIND(root->right, chapter);
}

// Hàm xóa một node trong cây
NODE* DELETE_NODE(NODE* root, int chapter) {
    if (IS_EMPTY(root)) return nullptr;

    if (chapter < root->chapter) {
        root->left = DELETE_NODE(root->left, chapter);
    } else if (chapter > root->chapter) {
        root->right = DELETE_NODE(root->right, chapter);
    } else {
        // Trường hợp tìm thấy node cần xóa
        if (IS_EMPTY(root->left)) {
            NODE* temp = root->right;
            delete root;
            return temp;
        }
        if (IS_EMPTY(root->right)) {
            NODE* temp = root->left;
            delete root;
            return temp;
        }

        // Node có cả hai con: tìm giá trị nhỏ nhất ở cây con phải
        NODE* temp = root->right;
        while (temp->left) temp = temp->left;

        root->chapter = temp->chapter;
        root->page = temp->page;
        root->section = temp->section;
        root->subsection = temp->subsection;

        root->right = DELETE_NODE(root->right, temp->chapter);
    }
    return root;
}

// Duyệt cây theo thứ tự trước (tiền tố)
void PREFIX(NODE* root) {
    if (IS_EMPTY(root)) return;
    cout << "Chapter: " << root->chapter 
         << ", Pages: " << root->page 
         << ", Sections: " << root->section 
         << ", Subsections: " << root->subsection << endl;
    PREFIX(root->left);
    PREFIX(root->right);
}

int main() {
    NODE* root = nullptr;

    // Thêm dữ liệu
    root = INSERT(root, 1, 100, 5, 10);
    root = INSERT(root, 2, 200, 8, 15);
    root = INSERT(root, 3, 150, 6, 12);

    // Hiển thị cấu trúc cây
    cout << "Tree structure (Prefix traversal):" << endl;
    PREFIX(root);

    // Đếm số chương
    cout << "\nNumber of chapters: " << NUM_OF_CHAP(root) << endl;

    // Tìm chương dài nhất
    int maxPages = 0;
    NODE* longest = MAX_LEN(root, maxPages);
    if (longest) {
        cout << "Longest chapter: Chapter " << longest->chapter 
             << " with " << maxPages << " pages." << endl;
    }

    // Tìm và xóa một chương
    int chapterToDelete = 2;
    cout << "\nDeleting chapter " << chapterToDelete << "..." << endl;
    root = DELETE_NODE(root, chapterToDelete);

    // Hiển thị lại cây
    cout << "Tree structure after deletion:" << endl;
    PREFIX(root);

    return 0;
}
