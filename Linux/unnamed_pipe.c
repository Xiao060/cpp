#include <stdio.h>
#include <strings.h>


int main(int argc, char* argv[]) {

    FILE* pf = popen("ls ~", "r");

    char buf[1024];

  
    bzero(buf, sizeof(buf));
    // fscanf(pf, "%s", buf);
    fread(buf, 1, sizeof(buf), pf);
    printf("%s\n", buf);

    fclose(pf);

    return 0;
}