bool Rqui_prime(int x)//x不能超int   /// shizhushuyes = true
{
    srand(time(0));
    int n = log(x)+7;
    if(quick_mod(7,x-1,x) != 1){
        return false;
    }
    for(int i = 0; i < n; i++){
        long long k = rand()%10000+7;
        if((k%x)&&(quick_mod(k,x-1,x)!=1)){	/// 快速幂{
            return false;
        }
    }

    return true;
}
