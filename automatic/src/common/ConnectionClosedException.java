package common;


public class ConnectionClosedException
  extends Exception
{
  private static final long serialVersionUID = 1L;
  
  public ConnectionClosedException()
  {
    super("Server closed connection");
  }
}
