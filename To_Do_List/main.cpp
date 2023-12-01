#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Job {
private:
    string  _job;
    int     _p;

public:
    Job() {}
    Job(string job, int p):_job(job), _p(p) {}
    ~Job() {}

    void show_job() { cout << _job; }
    int priority() { return _p; }
    Job & operator=(const Job &job) {
		_job = job._job;
		_p = job._p;
		return *this;
	}
};

class TODOList {
private:
    vector<Job> _maxheap;

    void switch_job(int a, int b) {
        Job tmp;

        tmp = _maxheap[a];
        _maxheap[a] = _maxheap[b];
        _maxheap[b] = tmp;
    }

public:
    TODOList() : _maxheap(0) {}
    ~TODOList() {}

    // root on pos 0
    // left child = 2n+1, right child = 2n+2
    // For node=n, father index = (n-1)/2

    // 加到最後一點，然後跟父節點比大小，若比他大，則交換。
    void insert(Job job) {
        int n=0;

        n = _maxheap.size();
        _maxheap.push_back(job);
        do {
            if (n < 1) break;

            if (_maxheap[n].priority() > _maxheap[(n-1)/2].priority()) {
                switch_job((n-1)/2, n);

                n = (n-1)/2;
            } else {
                break;
            }
        } while (n > 0);
    }

    // 跟最後一點交換，後從root開始跟childs比大小，直到沒有比較小。
    Job extract_max() {
        int n=_maxheap.size()-1;
        Job node=_maxheap[0];

        switch_job(0, n);

        // node = _maxheap[n];
        _maxheap.pop_back();

        n = 0;
        while (n < _maxheap.size()) {
            int left=2*n+1, right=2*n+2;

            if (_maxheap[left].priority() > _maxheap[right].priority()) {
                if ((_maxheap[n].priority() < _maxheap[left].priority()) && (left < _maxheap.size())) {
                    switch_job(n, left);
                    n = left;
                } else {
                    break;
                }
            } else {
                if ((_maxheap[n].priority() < _maxheap[right].priority()) && (right < _maxheap.size())) {
                    switch_job(n, right);
                    n = right;
                } else {
                    break;
                }
            }
        }

        return node;
    }

    void show() {
        for (int i=0; i<_maxheap.size(); i++) {
            cout << _maxheap[i].priority() << " ";
        }
        cout << endl;
    }
};

int main()
{
    TODOList job_list = TODOList();
    int p, i, n;
    string s;
    Job job;

    cin >> n;
    for (i=0; i<n; i++) {
        cin >> s;
        cin >> p;
        job_list.insert(Job(s, p));
    }

    cout << "First three things to do:" << endl;
    for (i=0; i<3; i++) {
        job_list.extract_max().show_job();
        cout << endl;
    }
}
