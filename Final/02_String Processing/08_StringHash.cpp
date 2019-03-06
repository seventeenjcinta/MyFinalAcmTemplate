typedef unsigned long long ull;
const ull Seed_Pool[] = {146527, 19260817};
const ull Mod_Pool[] = {1000000009, 998244353};
struct Hash
{
    ull SEED, MOD;
    vector<ull> p, h;
    Hash() {}
    Hash(const string& s, const int& seed_index, const int& mod_index)
    {
        SEED = Seed_Pool[seed_index];
        MOD = Mod_Pool[mod_index]; 
        int n = s.length();
        p.resize(n + 1), h.resize(n + 1);
        p[0] = 1;
        for (int i = 1; i <= n; i++) p[i] = p[i - 1] * SEED % MOD;
        for (int i = 1; i <= n; i++) h[i] = (h[i - 1] * SEED % MOD + s[i - 1]) % MOD;
    }
    ull get(int l, int r) { return (h[r] - h[l] * p[r - l] % MOD + MOD) % MOD; }
    ull substr(int l, int m) { return get(l, l + m); }
};