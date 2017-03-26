package common;


public class Protocol
{
  public static final int COM_LIST_NG = 1;
  
  public static final int COM_CREATE_NG = 2;
  
  public static final int COM_DELETE_NG = 3;
  
  public static final int COM_LIST_ART = 4;
  
  public static final int COM_CREATE_ART = 5;
  
  public static final int COM_DELETE_ART = 6;
  public static final int COM_GET_ART = 7;
  public static final int COM_END = 8;
  public static final int ANS_LIST_NG = 20;
  public static final int ANS_CREATE_NG = 21;
  public static final int ANS_DELETE_NG = 22;
  public static final int ANS_LIST_ART = 23;
  public static final int ANS_CREATE_ART = 24;
  public static final int ANS_DELETE_ART = 25;
  public static final int ANS_GET_ART = 26;
  public static final int ANS_END = 27;
  public static final int ANS_ACK = 28;
  public static final int ANS_NAK = 29;
  public static final int PAR_STRING = 40;
  public static final int PAR_NUM = 41;
  public static final int ERR_NG_ALREADY_EXISTS = 50;
  public static final int ERR_NG_DOES_NOT_EXIST = 51;
  public static final int ERR_ART_DOES_NOT_EXIST = 52;
  public static final int ERR_UNSPECIFIED = 53;
  
  public Protocol() {}
  
  public static String codeString(int code)
  {
    switch (code) {
    case 1:  return "COM_LIST_NG";
    case 2:  return "COM_CREATE_NG";
    case 3:  return "COM_DELETE_NG";
    case 4:  return "COM_LIST_ART";
    case 5:  return "COM_CREATE_ART";
    case 6:  return "COM_DELETE_ART";
    case 7:  return "COM_GET_ART";
    case 8:  return "COM_END";
    case 20: 
      return "ANS_LIST_NG";
    case 21:  return "ANS_CREATE_NG";
    case 22:  return "ANS_DELETE_NG";
    case 23:  return "ANS_LIST_ART";
    case 24:  return "ANS_CREATE_ART";
    case 25:  return "ANS_DELETE_ART";
    case 26:  return "ANS_GET_ART";
    case 27:  return "ANS_END";
    case 28:  return "ANS_ACK";
    case 29:  return "ANS_NAK";
    case 40: 
      return "PAR_STRING";
    case 41:  return "PAR_NUM";
    case 50: 
      return "ERR_NG_ALREADY_EXISTS";
    case 51:  return "ERR_NG_DOES_NOT_EXIST";
    case 52:  return "ERR_ART_DOES_NOT_EXIST";
    case 53:  return "ERR_UNSPECIFIED";
    }
    return "";
  }
}
