#include <iostream>
// Heap 
// Min heap - вверху наименьший элемент 
// Max heap - вверху наибольший элемент

struct TreeNode {
    /* узел дерева */
    int val{0};
    TreeNode* left{nullptr};
    TreeNode* right{nullptr};
};

// левый ребенок < корень < правый ребенок
class BST {
    public:
    // бинарное дерево поиска для int-ов
    BST() {}
    // добавление узла
    void push(int val) {
        // надо понять, куда нам добавлять новый лист
        if (root_ == nullptr) {
            // дерево еще пустое, просто создаем корень
            root_ = new TreeNode;
            root_->val = val;
            return;
        }
        TreeNode* temp = root_;
        while (temp->left || temp->right) {
            if (temp->val > val) {
                if (temp->left) temp = temp->left;
                else {
                    // если влево идти больше некуда
                    temp->left = new TreeNode;
                    temp->left->val = val;
                }
            } else if (temp->val < val) {
                if (temp->right) temp = temp->right;
                else {
                    // если влево идти больше некуда
                    temp->right = new TreeNode;
                    temp->right->val = val;
                }
            } else {
                return; // такой узел уже есть
            }
        }
    }

    TreeNode* find(int val) {
        TreeNode* temp = root_;
        while (temp) {
            if (temp->val == val) return temp;
            if (temp->val > val) temp = temp->left;
            else temp = temp->right;
        }
        return nullptr;  // если ничего не нашли
    }

    void remove(int val) {
        // мы должны кикнуть узел дерева, не поломав его
        TreeNode* temp = root_;
        // мы ищем узел, который надо кикнуть, и дальше проверяем:
        // если у него детей нет, то просто спокойно удаляем
        // если у него есть только 1 ребенок, то просто соединяем родителя с ребенком, 
        // а сам узел удаляем
        // если есть 2 ребенка, то дальше смотрим: если у одного из них нет симметричного
        // ребенка ИЛИ вообще нет детей, то ставим его и меняем ссылки
        // если же у обоих есть все дети, то мы будем брать самого левого из правого 
        // поддерева

        // шаг 1 - ищем узел
        if (temp->val != val) { // если кикнуть надо не корень
            TreeNode* prev = temp;
            while (temp) {
                if (temp->val == val) break;  // нашли
                if (temp->val > val) {
                    prev = temp;
                    temp = temp->left;
                } else {
                    prev = temp;
                    temp = temp->right;
                }
            }
            // итог: prev хранит родителя, temp - то, что надо удалить
            if (temp == nullptr) return;  // не нашли, такого узла нет

            if (temp->left == nullptr && temp->right == nullptr) {
                if (temp == prev->left) {
                    prev->left = nullptr;
                } else {
                    prev->right = nullptr;
                }
                delete temp;
                return;
            }
            if (temp->right != nullptr && temp->left == nullptr) {
                // только правый ребенок
                if (temp == prev->left) {
                    prev->left = temp->right;
                } else {
                    prev->right = temp->right;
                }
                delete temp;
                return;
            }
            if (temp->right == nullptr && temp->left != nullptr) {
                // только левый ребенок
                if (temp == prev->left) {
                    prev->left = temp->left;
                } else {
                    prev->right = temp->left;
                }
                delete temp;
                return;
            }
            // есть оба ребенка
            if (temp->left->right == nullptr) {
                // если у левого ребенка нет правого, то просто присобачим левого выше
                if (temp == prev->left) {
                    prev->left = temp->left;
                } else {
                    prev->right = temp->left;
                }
                temp->left->right = temp->right;
                delete temp;
                return;
            }
            if (temp->right->left == nullptr) {
                // если у правого ребенка нет левого, то просто присобачим правого выше
                if (temp == prev->left) {
                    prev->left = temp->right;
                } else {
                    prev->right = temp->right;
                }
                temp->right->left = temp->left;
                delete temp;
                return;
            }
            TreeNode* to_replace = temp->right;
            while (to_replace->left->left) to_replace = to_replace->left;
            to_replace->left->right = temp->right;
            to_replace->left->left = temp->left;
            if (temp == prev->left) {
                prev->left = to_replace->left;
            } else {
                prev->right = to_replace->left;
            }
            // чтобы у нас лист не мог ссылаться на корень выше
            to_replace->left = nullptr;
            delete temp;
        }
    }

    private:

    TreeNode* root_{nullptr};
};
