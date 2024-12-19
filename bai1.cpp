#include <iostream>

using namespace std;

struct Node {
    int chapter, page, section, subsection;
    Node* left, *right;

    Node(int c, int p, int s, int subs) {
        chapter = c;
        page = p;
        section = s;
        subsection = subs;
        left = right = nullptr;
    }
};

Node* insert(Node* root, int c, int p, int s, int subs) {
    if (!root) {
        return new Node(c, p, s, subs);
    }

    if (c < root->chapter) {
        root->left = insert(root->left, c, p, s, subs);
    } else if (c > root->chapter) {
        root->right = insert(root->right, c, p, s, subs);
    }

    return root;
}

int countChapters(Node* root) {
    if (!root) {
        return 0;
    }
    return 1 + countChapters(root->left) + countChapters(root->right);
}

Node* findMaxChapter(Node* root) {
    if (!root) {
        return nullptr;
    }

    Node* maxNode = root;
    Node* current = root->right;

    while (current) {
        maxNode = current;
        current = current->right;
    }

    return maxNode;
}

Node* deleteNode(Node* root, int chapter) {
    if (!root) {
        return root;
    }

    if (chapter < root->chapter) {
        root->left = deleteNode(root->left, chapter);
    } else if (chapter > root->chapter) {
        root->right = deleteNode(root->right, chapter);
    } else {
        // Node with one or no child
        if (!root->left) {
            Node* temp = root->right;
            delete root;
            return temp;
        } else if (!root->right) {
            Node* temp = root->left;
            delete root;
            return temp;
        }

        // Node with two children: Get the inorder successor (smallest
        // in the right subtree)
        Node* temp = findMaxChapter(root->left);
        root->chapter = temp->chapter;
        root->page = temp->page;
        root->section = temp->section;
        root->subsection = temp->subsection;
        root->left = deleteNode(root->left, temp->chapter);
    }
    return root;
}

void preorderTraversal(Node* root) {
    if (!root) {
        return;
    }
    cout << "Chapter: " << root->chapter << endl;
    cout << "Page: " << root->page << " Section: " << root->section << " Subsection: " << root->subsection << endl;
    preorderTraversal(root->left);
    preorderTraversal(root->right);
}

int main() {
    Node* root = nullptr;

    int chapter, page, section, subsection;

    for (int i = 0; i < 2; i++) {
        cout << "Chapter: ";
        cin >> chapter;
        cout << "Page: ";
        cin >> page;
        cout << "Section: ";
        cin >> section;
        cout << "Subsection: ";
        cin >> subsection;

        root = insert(root, chapter, page, section, subsection);
    }

    preorderTraversal(root);

    cout << "Number of chapters: " << countChapters(root) << endl;
    Node* maxChapterNode = findMaxChapter(root);
    cout << "Longest chapter: " << maxChapterNode->chapter << endl;

    // Delete a chapter (e.g., chapter 3)
    root = deleteNode(root, 3);

    preorderTraversal(root);

    return 0;
}
