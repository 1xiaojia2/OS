#include <exe/shell.h>
#include <stdio.h>
#include <stddef.h>
#include <drivers/keryboard.h>
#include <asm/cpu.h>
#include <ds/ioqueue.h>
#include <drivers/console.h>
#include <kernel/tty.h>
#include <string.h>
#include <drivers/time.h>
#include <kernel/sys/syscall.h>

#define CMD_MAX_LENGTH    100
#define CMD_MAX_ARGS        10
char command_buffer[CMD_MAX_LENGTH] = {0};
char *command_tokens[CMD_MAX_ARGS];

void show_time();

void promote(){
    console_write("[Ryan@localhost /]$ ");
}

void read_command(char *buf){

    char *pos = buf;

    while ((pos - buf) < CMD_MAX_LENGTH - 1)
    {
        *pos = ioq_getchar(&kbd_buf);
        switch (*pos)
        {
        case '\n':  /* Exit */
            *pos = '\0';
            console_putchar('\n');
            // Only way to exit.
            return ;

        case '\b':
            if(buf[0] != '\b'){
                console_putchar(*pos);
                *pos-- = '\0';
            }
            break;
        case '\t':  /* Ignore */
            break;
        
        default:
            console_putchar(*pos++);
            break;
        }
    }
}

size_t parse_command(char *cmd_buf){
    if(!cmd_buf[0]) return;

    /*
        cmd_buffer layout:
        [command  args1 args2 ... '\0''\0']
    */
   size_t i = 0;
    char *ptr = cmd_buf;
    while (*ptr != '\0')
    {
        if(*ptr == ' ')
            *ptr = '\0';
        ptr++;
    }
    ptr = cmd_buf;
    while (*ptr != '\0')
    {
        if(*ptr != '\0'){
            command_tokens[i++] = ptr;
            while (*ptr != '\0')
                ptr++;
        }
        ptr++;
    }
    return i;    
}

void exec_command(size_t token_nr){
    if(token_nr == 0) return;
    if(!strcmp(command_tokens[0], "clear")){
        bare_cls();
    }
    else if(!strcmp(command_tokens[0], "time")){
        bare_show_time();
    }
    else if(!strcmp(command_tokens[0], "echo")){
        for (size_t i = 1; i < token_nr; i++)
            // printf("args[%d]: *%s* ", i, command_tokens[i]);
            printf("%s", command_tokens[i]);
        printf("\n");
    }
    else if(!strcmp(command_tokens[0], "roll")){
        bare_roll_line();
    }
    else if(!strcmp(command_tokens[0], "nroll")){
        bare_cancel_roll();
    }
    else if(!strcmp(command_tokens[0], "help")){
        
    }
    else{
        printf("[%s] is not a command.\n", command_tokens[0]);
    }

}


void shell(){
    while (1)
    {
        promote();
        memset(&command_buffer, 0, CMD_MAX_LENGTH);
        memset(&command_tokens, 0, CMD_MAX_ARGS*sizeof(char *));
        cli();
        read_command(&command_buffer);
        sti();
        int toke_nr = parse_command(&command_buffer);
        exec_command(toke_nr);
    }
}
