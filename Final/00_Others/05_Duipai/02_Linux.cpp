int main()
{
    for(int i = 1; i <= 1000; i ++){
        system("./make");
        system("./ab1");
        system("./ab2");
        printf("%d : ",i);
        if(system("diff ab1.out ab2.out")){
            printf("WA\n");
            return 0;
        }
        else{
            printf("AC\n");
        }
    }

    return 0;
}
