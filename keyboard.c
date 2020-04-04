#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/input.h>
#include "biz_pi_KeyBoard.h"

#define KEY_EL(idx, val) [idx] = val

JNIEXPORT jint JNICALL Java_biz_pi_KeyBoard_open(JNIEnv *env, jobject, jstring name) {
    char *ptr = GetStringUTFChars(env, name, true);
    int fd;
    if (ptr == NULL) 
        return -1;
    fd = open(ptr, O_RDONLY);
    ReleaseStringUTFChars(env, name, ptr);
    return fd;
}

JNIEXPORT void JNICALL Java_biz_pi_KeyBoard_close(JNIEnv *, jobject, jint fd) {
    if (fd >= 0)
        close(fd);
}

static char KEYS[KEY_MAX + 1] = {
    [0 ... KEY_MAX] = '\0',
    KEY_EL(KEY_1, '1'), KEY_EL(KEY_2, '2'),
    KEY_EL(KEY_3, '3'), KEY_EL(KEY_4, '4'),
    KEY_EL(KEY_5, '5'), KEY_EL(KEY_6, '6'),
    KEY_EL(KEY_7, '7'), KEY_EL(KEY_8, '8'),
    KEY_EL(KEY_9, '9'), KEY_EL(KEY_0, '0'),
    KEY_EL(KEY_MINUS, '-'), KEY_EL(KEY_EQUAL, '='),
    KEY_EL(KEY_BACKSPACE, '\b'), KEY_EL(KEY_TAB, '\t'),
    KEY_EL(KEY_Q, 'q'),			KEY_EL(KEY_W, 'w'),
    KEY_EL(KEY_E, 'e'),			KEY_EL(KEY_R, 'r'),
    KEY_EL(KEY_T, 't'),			KEY_EL(KEY_Y, 'y'),
    KEY_EL(KEY_U, 'u'),			KEY_EL(KEY_I, 'i'),
    KEY_EL(KEY_O, 'o'),			KEY_EL(KEY_P, 'p'),
    KEY_EL(KEY_LEFTBRACE, '['),		KEY_EL(KEY_RIGHTBRACE, ']'),
    KEY_EL(KEY_ENTER, '\n'),		KEY_EL(KEY_LEFTCTRL, '\0'),
    KEY_EL(KEY_A, 'a'),			KEY_EL(KEY_S, 's'),
    KEY_EL(KEY_D, 'd'),			KEY_EL(KEY_F, 'f'),
    KEY_EL(KEY_G, 'g'),			KEY_EL(KEY_H, 'h'),
    KEY_EL(KEY_J, 'j'),			KEY_EL(KEY_K, 'k'),
    KEY_EL(KEY_L, 'l'),			KEY_EL(KEY_SEMICOLON, ';'),
    KEY_EL(KEY_APOSTROPHE, '\''),		KEY_EL(KEY_GRAVE, '`'),
    KEY_EL(KEY_LEFTSHIFT, '\0'),		KEY_EL(KEY_BACKSLASH, '\\'),
    KEY_EL(KEY_Z, 'z'),			KEY_EL(KEY_X, 'x'),
    KEY_EL(KEY_C, 'c'),			KEY_EL(KEY_V, 'v'),
    KEY_EL(KEY_B, 'b'),			KEY_EL(KEY_N, 'n'),
    KEY_EL(KEY_M, 'm'),			KEY_EL(KEY_COMMA, ','),
    KEY_EL(KEY_DOT, '.'),			KEY_EL(KEY_SLASH, '/'),
    KEY_EL(KEY_RIGHTSHIFT, '\0'),		KEY_EL(KEY_KPASTERISK, '\0'),
    KEY_EL(KEY_LEFTALT, '\0'),		KEY_EL(KEY_SPACE, ' '),
    KEY_EL(KEY_CAPSLOCK, '\0')
};




// struct input_event buff;
// int main(int argc, char *argv[])
// {
//     int fd = open("/dev/input/event0", O_RDONLY);
//     if (fd < 0) { 
//         perror("can not open device usbscanner!"); 
//         exit(1); 
//     } 
//     int i = 0;
//     printf("--fd:%d--\n",fd);
//     while(1)
//     {
//         int i = read(fd,&buff,sizeof(struct input_event));
//         printf("%d", i);
//         printf("type:%d code:%d value:%d\n",buff.type,buff.code,buff.value); 
//     }
//     close(fd); 
//     return 1;
// }
