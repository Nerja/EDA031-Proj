package common;









public class ProtocolViolationException
  extends Error
{
  private static final long serialVersionUID = 1L;
  








  public ProtocolViolationException(String method, int expectedCode, int receivedCode)
  {
    super(method + ". Expected " + translateToString(expectedCode) + ", received " + translateToString(receivedCode));
  }
  







  public ProtocolViolationException(String method, String message)
  {
    super(method + ". " + message + ".");
  }
  
  private static String translateToString(int code) {
    String s = Protocol.codeString(code);
    if (s == "") {
      s = "Unspecified code: (" + String.valueOf(code) + ")";
    }
    return s;
  }
}
