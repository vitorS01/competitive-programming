struct Erasable_PQ {
    priority_queue<int> vals, eras;

    Erasable_PQ() {

    }

    void insert(int x) {
        vals.push(x);
    }

    void erase(int x) {
        eras.push(x);
    }

    // return 0 if empty
    int get_max() {
        while (!eras.empty() && vals.top() == eras.top()) {
            eras.pop();
            vals.pop();
        }

        return (vals.empty() ? 0 : vals.top()); 
    }
};
