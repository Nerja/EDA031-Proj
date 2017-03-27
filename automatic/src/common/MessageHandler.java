package common;

import java.io.IOException;








public class MessageHandler
{
  private Connection conn;

  
  public MessageHandler(Connection conn)
  {
    this.conn = conn;
  }
  






  
  private void sendByte(int code) throws ConnectionClosedException {
    try {
      conn.write((char)code);
    } catch (IOException e) {
      throw new ConnectionClosedException();
    }
  }
  






  public void sendCode(int code)
    throws ConnectionClosedException
  {
    sendByte(code);
  }
  






  public void sendInt(int value)
    throws ConnectionClosedException
  {
    sendByte(value >> 24 & 0xFF);

    sendByte(value >> 16 & 0xFF);

    sendByte(value >> 8 & 0xFF);

    sendByte(value & 0xFF);

  }
  






  public void sendIntParameter(int param)
    throws ConnectionClosedException
  {
    sendCode(41);
    sendInt(param);
  }
  







  public void sendStringParameter(String param)
    throws ConnectionClosedException
  {
    sendCode(40);
    sendInt(param.length());
    for (int i = 0; i < param.length(); i++) {
      sendByte(param.charAt(i));

    }
  }
  
  private int recvByte() throws ConnectionClosedException {
    int code = conn.read();
    if (code == 1000) {
      throw new ConnectionClosedException();
    }
    return code;
  }
  





  public int recvCode()
    throws ConnectionClosedException
  {
    int code = recvByte();

    return code;
  }
  





  public int recvInt()
    throws ConnectionClosedException
  {
    int b1 = recvByte();

    int b2 = recvByte();

    int b3 = recvByte();

    int b4 = recvByte();

    
    return b1 << 24 | b2 << 16 | b3 << 8 | b4;
  }
  





  public int recvIntParameter()
    throws ConnectionClosedException
  {
    int code = recvCode();
    if (code != 41) {
      throw new ProtocolViolationException("Receive numeric parameter", 
        41, code);
    }
    return recvInt();
  }
  





  public String recvStringParameter()
    throws ConnectionClosedException
  {
    int code = recvCode();
    if (code != 40) {
      throw new ProtocolViolationException("Receive string parameter", 
        40, code);
    }
    int n = recvInt();
    if (n < 0) {
      throw new ProtocolViolationException("Receive string parameter", 
        "Number of characters < 0");
    }
    StringBuffer result = new StringBuffer(n);
    for (int i = 1; i <= n; i++) {
      char ch = (char)conn.read();
      result.append(ch);
    }
    return result.toString();
  }
}
