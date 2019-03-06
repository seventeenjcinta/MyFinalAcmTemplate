vector<int> id;

int Getid(int x)	/// 1 ¿ªÊ¼±êºÅ
{
    return lower_bound(id.begin(), id.end(), x) - id.begin() + 1;
}

void G()
{
    sort(id.begin(), id.end());
    id.erase(unique(id.begin(), id.end()), id.end());
}
