package common;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.PrintStream;
import java.net.Socket;









public class Connection
{
  public static final int CONNECTION_CLOSED = 1000;
  private Socket mySocket;
  private InputStream input;
  private OutputStream output;
  
  public Connection(String host, int port)
  {
    mySocket = null;
    try {
      mySocket = new Socket(host, port);
      input = mySocket.getInputStream();
      output = mySocket.getOutputStream();
    }
    catch (IOException localIOException) {localIOException.printStackTrace();}
  }
  





  public boolean isConnected()
  {
    return mySocket != null;
  }
  






  public void write(char data)
    throws IOException
  {
    if (mySocket == null) {
      error("write attempted on a not properly opened Connection");
    }
    output.write(data);
  }
  





  public int read()
  {
    if (mySocket == null) {
      error("read attempted on a not properly opened Connection");
    }
    try {
      int data = input.read();
      return data != -1 ? data : 1000;
    }
    catch (IOException e) {}
    return 1000;
  }
  
  private void error(String msg)
  {
    System.err.println(msg);
    System.exit(0);
  }
}
