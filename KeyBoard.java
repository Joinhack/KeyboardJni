package biz.pi;

public class KeyBoard {

    public native int open(String name);

    public String readLine(int fd) {
        return new String(readline(fd));
    }

    private native byte[] readline(int fd);

    public native void close(int fd);

}