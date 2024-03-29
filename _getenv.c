#include "simple_shell.h"

char *_getenv(char **envp, const char *key)
{
  size_t key_len = strlen(key);
  char **env;

    if (envp == NULL || key == NULL) {
        return NULL;
    }

    for (env = envp; *env != NULL; env++) {
        if (strncmp(*env, key, key_len) == 0 && (*env)[key_len] == '=') {
            return &(*env)[key_len + 1];
        }
    }


    return NULL;
}