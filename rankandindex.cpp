struct Node {
  int val;
  Node *l, *r;
};


Node* tree;
Node* _initTree(int N) {
  int leftSize = N/2;
  int rightSize = N-leftSize;
  Node* ret = new Node();
  tree->val = 0;
  if (N<=1) {
    tree->l = _initTree(leftSize);
    tree->r = _initTree(rightSize);
  } else {
    tree->l = nullptr;
    tree->r = nullptr;
  }
  return ret;
}
void initTree(int N) {
  tree = _initTree(N);
}

int Set(Node* tree, int N, int index, int val) {
  int leftSize = N/2;
  int rightSize = N-leftSize;
  
  if (N<=1) {
    if (tree->val == val) {
      return 0;
    } else {
      tree->val = val;
      if (val == 1) {
        return 1;
      } else {
        return -1;
      }
    }
  }
  
  if (index < leftSize) {
    int r = Set(tree->l, leftSize, index, val);
    tree->val += r;
    return r;
  } else {
    int r = Set(tree->r, rightSize, index - leftSize, val);
    tree->val += r;
    return r;
  }
}

int Rank(Node* tree, int N, int index) {
  int leftSize = N/2;
  int rightSize = N-leftSize;
  
  if (N<=1) {
    return tree->val;
  }
  
  if (index < leftSize) {
    int r = Rank(tree->l, leftSize, index);
    return r;
  } else {
    int r = Rank(tree->r, rightSize, index - leftSize);
    return r + tree->l.val;
  }
}