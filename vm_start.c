
#include <stdio.h>
#include <Windows.h>

int main(int argc, char *argv[])
{
    register int i, j, l, nb_nic,skip;
    FILE *fp;

    char vm_name[1024];
    char result[4096];
    char buffer[4096];

    char t_nic[64][256];
    
    if (argc != 2)
    {
        fprintf(stderr, "ERROR: Exactly 1 argument expected: \"VM Name\"\n");
        exit(-1);
    }
    strcpy(vm_name, argv[1]);

    // first let's enumerate all nic
    fp = _popen("VBoxManage.exe list bridgedifs  | findstr -i VBoxNetworkName", "r");
    {
        for (nb_nic=0 ; fgets(buffer, 4095, fp); ++nb_nic)
        {
            for (i = 0; buffer[i] && buffer[i] != '-'; ++i); ++i;   // skip to first char after '-'
            for (j = 0; buffer[i] && buffer[i] != '\n';) result[j++] = buffer[i++]; result[j] = '\0';
            strcpy(t_nic[nb_nic++], result);
        }
    }
    // then let's select the first wired interface found if anyt
    if (nb_nic > 0)         // If no nic found just do nothing!
    {
        if (nb_nic == 1) strcpy(result, t_nic[0]);
        else
        {
            for (i=0 ; i<nb_nic-1 ; ++i)  // We keep the last interface name if all previous are skipped!
            {                               // So we keep the wireless interface if no wired interface found...
                strcpy(buffer, t_nic[0]); l = strlen(buffer);
                for (skip=j=0 ; j<l ; ++j)
                {
                    if (!strncmp(buffer, "Wireless", strlen("Wireless"))) { skip = 1; break; }
                    if (!strncmp(buffer, "Wifi"    , strlen("Wifi"    ))) { skip = 1; break; }
                }
                if (skip) continue;     // if wireless interface is found, then skip it!
                break;                  // we stop on the 1st non wireless interface found!
            }
            strcpy(result, t_nic[i]);
        }
        printf("Selecting : \"%s\" network interface.\n", result);
        sprintf(buffer,"VBoxManage.exe modifyvm \"%s\" --bridgeadapter1 \"%s\"\n", vm_name,result);
        system(buffer);
    }
    sprintf(buffer,"VBoxManage.exe startvm \"%s\"\n", vm_name);
    system(buffer);
    return 0;
}
