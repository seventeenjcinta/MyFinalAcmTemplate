void Topology()
{
    int li;
    int Stop;

    li = n * m;
    Stop = 0;
    memset(vis, 0, sizeof(vis));
    for(int i = 0; i < li; i ++){
        if(!inde[i]){
            St[Stop] = i;
            Stop ++;
        }
        else{
            del[i] = 1;
        }
    }
    while(Stop){
        int now;

        now = St[Stop - 1];
        Stop --;
        del[now] = 0;
        for(int i = head[now]; i != -1; i = node[i].ne){
            inde[node[i].to] --;
            if(!inde[node[i].to]){
                St[Stop] = node[i].to;
                Stop ++;
            }
        }
    }
}
