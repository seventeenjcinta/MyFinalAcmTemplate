struct Node
{
  int to;
  int w;
  int ne;
};

Node node[N];
int head[N];
int top;

void add(int from, int to, int w)
{
  node[top].to = to;
  node[top].w = w;
  node[top].ne = head[from];
  head[from] = top;
  top ++;
}

for(int i = head[u]; i != -1; i = node[i].ne){
  /// ±éÀú
}

void ini()
{
  top = 0;
  memset(head, -1, sizeof(head));
}
