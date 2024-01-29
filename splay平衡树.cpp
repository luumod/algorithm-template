#include <bits/stdc++.h>

const int N = 5e4 + 10;
int n;
struct Node {
    int s[2]; //左右孩子
    int size; //当前为子树的根时的子树大小
    int cnt;  //当前同节点的个数
    int p;    //父亲
    int val;  //权值
    void init(int p, int val) { this->p = p, this->val = val, cnt = 1, size = 1; }
}tree[N];
int root, idx;
void push_up(int x) {
    //上移
    tree[x].size = tree[tree[x].s[0]].size + tree[tree[x].s[1]].size + tree[x].cnt;
}
void rotate(int x) {
    //------旋转-----
    //获取x的爸爸和爷爷
    int y = tree[x].p, py = tree[y].p;
    int k=(tree[y].s[1] == x);
    tree[y].s[k] = tree[x].s[k^1];
    tree[tree[x].s[k^1]].p = y;
    tree[x].s[k^1] = y;
    tree[y].p = x;
    tree[py].s[tree[py].s[1] == y] = x;
    tree[x].p = py;
    //上移，保存节点信息
    push_up(y), push_up(x);
}
void splay(int x, int k) {
    //核心操作：访问一个x节点并且把x移动到k位置的下面，如果k=0,则移动到根节点
    while (tree[x].p != k) {
        int y = tree[x].p, py = tree[y].p;
        if (py != k) {
            if ((tree[py].s[0] == y) ^ (tree[y].s[0] == x)){
                 rotate(x);
            }
            else{
                rotate(y);
            }
        }
        rotate(x);
    }
    if (k == 0) {
        root = x;
    }
}
void find(int v) {
    //查找v节点，并且把v旋转到根节点
    int x = root;
    while (tree[x].s[v > tree[x].val] && v != tree[x].val) {
        x = tree[x].s[v > tree[x].val];
    }
    splay(x, 0);
}
void insert(int v) {
    //插入v节点
    int x = root, px = 0;
    while (x && tree[x].val != v) {
        px = x, x = tree[x].s[v > tree[x].val];
    }
    if (x) {
        tree[x].cnt++;
    }
    else {
        x = ++idx;
        tree[px].s[v > tree[px].val] = x;
        tree[x].init(px, v);
    }
    splay(x, 0);
}
int getXPre(int v) {
    //查找v节点的前驱节点
    find(v);
    int x = root;
    if (tree[x].val < v) {
        return x;
    }
    x = tree[x].s[0];
    while (tree[x].s[1]) {
        x = tree[x].s[1];
    }
    splay(x,0);
    return x;
}
int getXSuf(int v) {
    //查找v节点的后继节点
    find(v);
    int x = root;
    if (tree[x].val > v) {
        return x;
    }
    x = tree[x].s[1];
    while (tree[x].s[0]) {
        x = tree[x].s[0];
    }
    splay(x,0);
    return x;
}
void del(int v) {
    //删除v节点，如果有多个，只删除一个
    int pre = getXPre(v);
    int suf = getXSuf(v);
    splay(pre, 0), splay(suf, pre);
    int Del = tree[suf].s[0];
    if (tree[Del].cnt > 1) {
        tree[Del].cnt--;
        splay(Del, 0);
    }
    else {
        tree[suf].s[0] = 0;
        splay(suf, 0);
    }
}
int query_rank(int x) {
    //获取x数字的排名
    find(x);
    return tree[tree[root].s[0]].size;
}
int query_val(int k) {
    //查询排名为k的数值
    int x = root;
    while (true) {
        int y = tree[x].s[0];
        if (tree[y].size + tree [x].cnt < k) {
            k -= (tree[y].size + tree[x].cnt);
            x = tree[x].s[1];
        }
        else if (tree[y].size >= k) {
            x = y;
        }
        else {
            break;
        }
    }
    splay(x, 0);
    return tree[x].val;
}
int main() {
    insert(-1e9), insert(1e9);
    std::cin >> n;
    for (int i = 1; i <= n; i++) {
        int op, x;
        std::cin >> op >> x;
        if (op == 1) {
            insert(x);
        }
        else if (op == 2) {
            del(x);
        }
        else if (op == 3) {
            std::cout << query_rank(x) << '\n';
        }
        else if (op == 4) {
            std::cout << query_val(x+1) << '\n';
        }
        else if (op == 5) {
            std::cout << tree[getXPre(x)].val << '\n';
        }
        else if (op == 6) {
            std::cout << tree[getXSuf(x)].val << '\n';
        }
    }
    return 0;
}