// while (dirrrr[i] != NULL)
//     {
//         struct dirent *pDirent;
//         DIR *pDir;
//         pDir = opendir(dirrrr[i]);
//         while ((pDirent = readdir(pDir)) != NULL)
//         {
//             char *namename = (char *)malloc(sizeof(char) * 2000);
//             sprintf(namename, "%s/%s", dirrrr[i], pDirent->d_name);
//             // printf("%s", namename);

//             if (opendir(namename) > 0)
//             {
//                 if (pDirent->d_name[0] != '.')
//                 {
//                     dirposs++;
//                     dirrrr[dirposs] = (char *)malloc(sizeof(char) * strlen(namename) + 10);
//                     strcpy(dirrrr[dirposs], namename);
//                 }
//             }
//             else
//             {

//                 if (strcmp(pDirent->d_name, ivin) == 0)
//                 {
//                     printf("%s\n", namename);
//                 }
//             }
//             free(namename);
//         }
//         closedir(pDir);
//         i++;
//     }