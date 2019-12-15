typedef char Key;
typedef struct { Key key; char information[1000]; } Node;
#define Ckey(A, N) (A.information[N])
#define Skey(A) (A.information)

extern Node NULLnode;
