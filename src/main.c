#include <string.h>
#include <gprolog.h>
#include <stdio.h>

static int
Main_Wrapper(int argc, char *argv[])
{
    int func;
    PlTerm arg[10];
    char str[100];
    char *sol[100];
    int i, nb_sol = 0;
    PlBool res;

    Pl_Start_Prolog(argc, argv);

    func = Pl_Find_Atom("anc");
    for (;;)
    {
        printf("\nEnter a name (or 'end' to finish): ");
        fflush(stdout);
        scanf("%s", str);

        if (strcmp(str, "end") == 0)
            break;

        Pl_Query_Begin(PL_TRUE);

        arg[0] = Pl_Mk_Variable();
        arg[1] = Pl_Mk_String(str);
        nb_sol = 0;
        res = Pl_Query_Call(func, 2, arg);
        while (res)
        {
            sol[nb_sol++] = Pl_Rd_String(arg[0]);
            res = Pl_Query_Next_Solution();
        }
        Pl_Query_End(PL_RECOVER);

        for (i = 0; i < nb_sol; i++)
            printf("  solution: %s\n", sol[i]);
        printf("%d solution(s)\n", nb_sol);
    }

    Pl_Stop_Prolog();
    return 0;
}

int
main(int argc, char *argv[])
{
    return Main_Wrapper(argc, argv);
}
