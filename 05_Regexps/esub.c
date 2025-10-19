#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

#define MAXGR 10

int main(int argc, char *argv[])
{
        if (argc != 4)
        {
                fprintf(stderr, "Not correct nubmer of arguments, 4 args is are needed");
                return 100;
        }

        char *regexStr = argv[1], *substitutionStr = argv[2], *sourceStr = argv[3];
        int num, i = 0;
        char c;
        regex_t regex;
        regmatch_t bags[MAXGR];

        int result = regcomp(&regex, regexStr, REG_EXTENDED);
        if (result != 0)
        {
                char errbuf[256];
                regerror(result, NULL, errbuf, sizeof(errbuf));
                fprintf(stderr, "Failed to perform regex, due to %s\n", errbuf);
                return result;
        }

        result = regexec(&regex, sourceStr, MAXGR, bags, 0);

        if (result == 0)
        {
                i = 0;
                printf("%.*s", bags[0].rm_so, sourceStr);
                while ((c = substitutionStr[i]) != '\0')
                {
                        if (c == '\\')
                        {
                                i++;
                                c = substitutionStr[i];
                                if (c == '\\')
                                        printf("%c", c);
                                else if ((num = c - '0') >= 0 && num <= 9)
                                {
                                        if (num > regex.re_nsub || num == 0 || bags[num].rm_so == 0)
                                        {
                                                fprintf(stderr, "Failed to perform substitution, due to bad bag count");
                                                regfree(&regex);
                                                return 100;
                                        }

                                        printf("%.*s", bags[num].rm_eo - bags[num].rm_so, sourceStr + bags[num].rm_so);
                                }
                        }
                        else
                                printf("%c", c);
                
                        i++;
                }
                printf("%s\n", sourceStr + bags[0].rm_eo);
        }
        else if (result == REG_NOMATCH)
        {
                printf("%s\n", sourceStr);
        }
        else
        {
                char errbuf[256];
                regerror(result, &regex, errbuf, sizeof(errbuf));
                fprintf(stderr, "Failed to perform regex, due to %s\n", errbuf);
                regfree(&regex);
                return result;
        }

        regfree(&regex);
        return 0;
}
