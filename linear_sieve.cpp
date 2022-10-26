auto Sieve = [&](const int& n) {
    vector<bool>isp(n, 1);
    vector<int> prime;
    for (int i = 2; i < n; ++i) {
        if (isp[i]) prime.emplace_back(i);
        for (auto& p : prime) {
            if (i * p > n) break; 
            isp[i * p] = 0; 
            if (i % p == 0) break;
        }
    }
    return prime;
};
