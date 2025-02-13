/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talin <talin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 10:46:19 by talin             #+#    #+#             */
/*   Updated: 2025/01/22 11:53:10 by talin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_env_from_proc() {
    FILE *file = fopen("/proc/self/environ", "r");
    if (!file) {
        perror("fopen");
        return;
    }

    char buffer[4096]; // Adjust size as needed
    size_t bytes_read = fread(buffer, 1, sizeof(buffer) - 1, file);
    fclose(file);

    if (bytes_read == 0) {
        perror("fread");
        return;
    }

    buffer[bytes_read] = '\0'; // Null-terminate the string

    // Print each environment variable
    char *var = buffer;
    while (var < buffer + bytes_read) {
        printf("%s\n", var);
        var += strlen(var) + 1; // Move to the next null-terminated string
    }
}

int main() {
    print_env_from_proc();
    return 0;
}
