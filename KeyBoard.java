package biz.pi;

public class KeyBoard {

    public native int open(String name);

    public String readLine(int fd) {
        return new String(readline(fd));
    }

    private native byte[] readline(int fd);

    public native void close(int fd);

    static {
        System.loadLibrary("keyboard");
    }

    public static void main(String argv[]) {
        
        KeyBoard keyBoard = new KeyBoard();
        int fd = keyBoard.open("/dev/input/event0");
        System.out.println(keyBoard.readLine(fd));
        keyBoard.close(fd);
    }
}