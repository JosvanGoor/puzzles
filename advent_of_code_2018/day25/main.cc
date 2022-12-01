#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Star
{
    int x;
    int y;
    int z;
    int t;
};

istream& operator>>(istream& in, Star &star)
{
    in >> star.x;
    in.ignore(); //ignore ','
    in >> star.y;
    in.ignore();
    in >> star.z;
    in.ignore();
    in >> star.t;
    in.ignore();

    return in;
}

ostream &operator<<(ostream &out, Star const &star)
{
    out << "[" << star.x << ", " << star.y << ", " << star.z << ", " << star.t << "]";
    return out;
}


size_t distance(Star const &lhs, Star const &rhs)
{
    int dist = abs(lhs.x - rhs.x)
        + abs(lhs.y - rhs.y)
        + abs(lhs.z - rhs.z)
        + abs(lhs.t - rhs.t);

    return dist;
}

bool in_cluster(vector<Star> const &cluster, Star const &star)
{
    for (Star clst : cluster)
    {
        if (distance(clst, star) <= 3)
            return true;
    }

    return false;
}

bool same_cluster(vector<Star> const &lhs, vector<Star> const &rhs)
{
    for (Star left : lhs)
    {
        for (Star right : rhs)
        {
            if (distance(left, right) <= 3)
                return true;
        }
    }

    return false;
}

int main()
{

    vector<Star> stars;

    while (cin)
    {
        Star star;
        cin >> star;
        stars.push_back(star);
    }

    // kickstart 1st cluster
    vector<vector<Star>> clusters;
    
    for (Star star : stars)
    {
        bool matched = false;

        for (vector<Star> &cluster : clusters)
        {
            if (in_cluster(cluster, star))
            {
                cluster.push_back(star);
                matched = true;
                break;
            }
        }

        if (!matched)
        {
            clusters.push_back({});
            clusters.back().push_back(star);
        }
    }

    bool merged = true;
    while (merged)
    {
        merged = false;
        for (size_t idx = 0; idx < clusters.size(); ++idx)
        {
            for (size_t jdx = idx + 1; jdx < clusters.size(); ++jdx)
            {
                if (same_cluster(clusters[idx], clusters[jdx]))
                {
                    clusters[idx].insert(clusters[idx].end(), clusters[jdx].begin(), clusters[jdx].end());
                    clusters.erase(clusters.begin() + jdx);
                    merged = true;
                    break;
                }
            }
            if (merged) break;
        }
    }

    for (vector<Star> cluster : clusters)
    {
        cout << "\n\nCluster:\n";
        for (Star star : cluster)
        {
            cout << "    Star: " << star << "\n";
        }
    }

    cout << "Num clusters: " << clusters.size() << "\n";
}   