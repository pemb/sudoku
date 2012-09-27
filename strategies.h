
int singles(int ***);

int (* strategies[])(int ***) = {singles};

int functions = sizeof(strategies)/sizeof(void *);

