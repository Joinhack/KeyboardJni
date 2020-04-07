#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <poll.h>
#include <linux/input.h>
#include <errno.h>
#include "biz_pi_KeyBoard.h"

#define KEY_EL(idx, val) [idx] = val

JNIEXPORT jint JNICALL Java_biz_pi_KeyBoard_open(JNIEnv *env, jobject o, jstring name) {
    jboolean isCopy = 0;
    int fd;
    const char *ptr = (*env)->GetStringUTFChars(env, name, &isCopy);
    if (ptr == NULL) 
        return -1;
    fd = open(ptr, O_RDONLY|O_NONBLOCK);
    (*env)->ReleaseStringUTFChars(env, name, ptr);
    return fd;
}

JNIEXPORT void JNICALL Java_biz_pi_KeyBoard_close(JNIEnv *env, jobject o, jint fd) {
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


JNIEXPORT jbyteArray JNICALL Java_biz_pi_KeyBoard_readline(JNIEnv *env, jobject o, jint fd) {
    struct pollfd fds[1];
    struct input_event evts[64];
    int prs, n, p, idx;
    jbyteArray rs = NULL;
    char buff[2048];
    fds[0].events = POLLIN;
    fds[0].fd = fd;
    idx = 0;
    while(1) {
        int i;
        char kv;
        if ((prs = poll(fds, 1, 200)) < 0) {
            printf("error code:%d, msg: %s\n", errno, strerror(errno));
            return rs;
        } else if (prs == 0) {
            if (idx > 0 && buff[idx - 1] == '\n') {
                break;
            }
        } else if (prs > 0) {
            n = read(fd, &evts, sizeof(evts));
            for (i = 0; i < sizeof(evts)/sizeof(struct input_event) && idx < sizeof(buff); i++) {
                if (evts[i].type == EV_SYN && i - 1 > 0) {
                    if (evts[i - 1].type == EV_KEY) {
                        if (evts[i - 1].value == 1 && (kv = KEYS[evts[i - 1].code]) != '\0') {
                            buff[idx++] = kv;
                        }
                    }
                }
            }
        }
    }
    if (idx > 0) {
        rs = (*env)->NewByteArray(env, idx);
        (*env)->SetByteArrayRegion(env, rs, 0, idx, buff);
    }
    return rs;
}
