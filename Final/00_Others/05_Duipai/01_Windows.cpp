/// Windows£¿
int main()
{
    int t = 1000;
    while(t --){
        system("datamaker > a+b.in");
        system("truely < a+b.in > truely.out");
        system("ask < a+b.in > ask.out");
        if(system("fc ask.out truely.out"))   break;
        cout << 6 << endl;
    }
    system("pause");
    return 0;
}
