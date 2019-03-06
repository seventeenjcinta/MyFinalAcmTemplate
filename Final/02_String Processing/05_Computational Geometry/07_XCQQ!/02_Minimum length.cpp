/// 最长点距 凸多边形直径
void Solve2(int num)
{
    int ymax=-1e5,ymin=1e5;
    int ymaxidx,yminidx;
    for(int i=1;i<=num;i++)
    {
        if(ch[i].y>ymax)
        {
            ymax=ch[i].y;
            ymaxidx=i;
        }
        if(ch[i].y<ymin)
        {
            ymin=ch[i].y;
            yminidx=i;
        }
    }
    int ans=dis2(ch[ymaxidx]-ch[yminidx]);
    ch[num+1]=ch[1];
    for(int t=1;t<=num;t++,yminidx=yminidx%num+1)
    {
        while(xmult(ch[yminidx+1],ch[ymaxidx+1],ch[yminidx])>xmult(ch[yminidx+1],ch[ymaxidx],ch[yminidx]))ymaxidx=ymaxidx%num+1;
        ans=max(ans,dis2(ch[ymaxidx]-ch[yminidx]));
        ans=max(ans,dis2(ch[ymaxidx]-ch[yminidx+1]));
    }
    printf("%d\n",ans);
}
