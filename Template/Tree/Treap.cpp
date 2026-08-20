mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

struct Treap {
    int data, priority;
    Treap* kids[2];
    int subsz;

    void recalc() {
        subsz = 1;
        for(Treap* t : kids) if(t!=nullptr) subsz+=t->subsz;
    }

    Treap(int data) : data(data) {
        kids[0] = nullptr;
        kids[1] = nullptr;
        priority = rng();
        recalc();
    }

    int size(Treap *t) {
        return (t==nullptr ? 0 : t->subsz);
    }

    pair<Treap*, Treap*> split(int amtlf) {
        if(size(kids[0]) >= amtlf) {
            if(kids[0]==nullptr) return {nullptr,this};
            auto lfres = kids[0]->split(amtlf);
            kids[0] = lfres.se;
            recalc();
            return{lfres.fi, this};
        }
        else {
            amtlf -= size(kids[0])+1;
            if(kids[1]==nullptr) return {this,nullptr};
            auto rtres = kids[1]->split(amtlf);
            kids[1] = rtres.fi;
            recalc();
            return {this,rtres.se};
        }
    }
};

Treap* merge(Treap *l, Treap *r) {
    if(l==nullptr) return r;
    if(r==nullptr) return l;

    if(l->priority < r->priority) {
        l->kids[1] = merge(l->kids[1],r);
        l->recalc();
        return l;
    } else {
        r->kids[0] = merge(l,r->kids[0]);
        r->recalc();
        return r;
    }
}
