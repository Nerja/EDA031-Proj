package common;



public class CommandHandler
{
  private MessageHandler mh;
  

  

  protected int[] groupIds;
  
  protected int[] articleIds;
  
  private static final int NE_GROUP_ID = 999999;
  
  private static final int NE_ART_ID = 888888;
  

  public CommandHandler(MessageHandler mh)
  {
    this.mh = mh;
  }
  












  public String[] listGroups()
    throws ConnectionClosedException, ProtocolViolationException
  {

    mh.sendCode(1);
    mh.sendCode(8);

    

    int code = mh.recvCode();
    checkCode("List groups", 20, code);
    
    int nbrGroups = mh.recvIntParameter();
    checkCondition(nbrGroups >= 0, "List groups", "Number of groups < 0");
    groupIds = new int[nbrGroups];
    String[] groupNames = new String[nbrGroups];
    for (int i = 0; i < nbrGroups; i++) {
      groupIds[i] = mh.recvIntParameter();
      groupNames[i] = mh.recvStringParameter();
    }
    code = mh.recvCode();
    checkCode("List groups", 27, code);

    return groupNames;
  }
  










  public int createGroup(String title)
    throws ConnectionClosedException, ProtocolViolationException
  {

    mh.sendCode(2);
    mh.sendStringParameter(title);
    mh.sendCode(8);

    
    int errorCode = 0;

    int code = mh.recvCode();
    checkCode("Create group", 21, code);
    code = mh.recvCode();
    if (code != 28) {
      checkCondition(code == 29, "Create group", 
        "Did not receive ANS_ACK or ANS_NAK");
      errorCode = mh.recvCode();
    }
    code = mh.recvCode();
    checkCode("Create group", 27, code);

    return errorCode;
  }
  










  public int deleteGroup(int groupIndex)
    throws ConnectionClosedException, ProtocolViolationException
  {
    int groupId = getGroupId(groupIndex);
;
    mh.sendCode(3);
    mh.sendIntParameter(groupId);
    mh.sendCode(8);

    
    int errorCode = 0;

    int code = mh.recvCode();
    checkCode("Delete group", 22, code);
    code = mh.recvCode();
    if (code != 28) {
      checkCondition(code == 29, "Create group", 
        "Did not receive ANS_ACK or ANS_NAK");
      errorCode = mh.recvCode();
    }
    code = mh.recvCode();
    checkCode("Delete group", 27, code);

    return errorCode;
  }
  










  public String[] listArticles(int groupIndex)
    throws ConnectionClosedException, ProtocolViolationException
  {
    int groupId = getGroupId(groupIndex);

    mh.sendCode(4);
    mh.sendIntParameter(groupId);
    mh.sendCode(8);

    
;
    int code = mh.recvCode();
    checkCode("List articles", 23, code);
    code = mh.recvCode();
    if (code != 28) {
      checkCondition(code == 29, "Create group", 
        "Did not receive ANS_ACK or ANS_NAK");
      code = mh.recvCode();
      code = mh.recvCode();

      return null;
    }
    int nbrArticles = mh.recvIntParameter();
    checkCondition(nbrArticles >= 0, "List articles", 
      "Number of groups < 0");
    articleIds = new int[nbrArticles];
    String[] articleNames = new String[nbrArticles];
    for (int i = 0; i < nbrArticles; i++) {
      articleIds[i] = mh.recvIntParameter();
      articleNames[i] = mh.recvStringParameter();
    }
    code = mh.recvCode();
    checkCode("List articles", 27, code);

    return articleNames;
  }
  

















  public int createArticle(int groupIndex, String title, String author, String text)
    throws ConnectionClosedException, ProtocolViolationException
  {
    int groupId = getGroupId(groupIndex);

    mh.sendCode(5);
    mh.sendIntParameter(groupId);
    mh.sendStringParameter(title);
    mh.sendStringParameter(author);
    mh.sendStringParameter(text);
    mh.sendCode(8);

    
    int errorCode = 0;

    int code = mh.recvCode();
    checkCode("Create article", 24, code);
    code = mh.recvCode();
    if (code != 28) {
      checkCondition(code == 29, "Create group", 
        "Did not receive ANS_ACK or ANS_NAK");
      errorCode = mh.recvCode();
    }
    code = mh.recvCode();
    checkCode("Create article", 27, code);

    return errorCode;
  }
  












  public int deleteArticle(int groupIndex, int articleIndex)
    throws ConnectionClosedException, ProtocolViolationException
  {
    int groupId = getGroupId(groupIndex);
    int articleId = getArticleId(articleIndex);

    mh.sendCode(6);
    mh.sendIntParameter(groupId);
    mh.sendIntParameter(articleId);
    mh.sendCode(8);

    
    int errorCode = 0;

    int code = mh.recvCode();
    checkCode("Delete article", 25, code);
    code = mh.recvCode();
    if (code != 28) {
      checkCondition(code == 29, "Create group", 
        "Did not receive ANS_ACK or ANS_NAK");
      errorCode = mh.recvCode();
    }
    code = mh.recvCode();
    checkCode("Delete article", 27, code);

    return errorCode;
  }
  













  public String[] getArticle(int groupIndex, int articleIndex)
    throws ConnectionClosedException, ProtocolViolationException
  {
    int groupId = getGroupId(groupIndex);
    int articleId = getArticleId(articleIndex);

    mh.sendCode(7);
    mh.sendIntParameter(groupId);
    mh.sendIntParameter(articleId);
    mh.sendCode(8);

    
    String[] result = null;

    int code = mh.recvCode();
    checkCode("Get article", 26, code);
    code = mh.recvCode();
    if (code != 28) {
      checkCondition(code == 29, "Create group", 
        "Did not receive ANS_ACK or ANS_NAK");
      result = new String[1];
      result[0] = String.valueOf(mh.recvCode());
    } else {
      result = new String[3];
      result[0] = mh.recvStringParameter();
      result[1] = mh.recvStringParameter();
      result[2] = mh.recvStringParameter();
    }
    code = mh.recvCode();
    checkCode("Delete article", 27, code);

    return result;
  }
  
  private int getGroupId(int groupIndex) {
    return (groupIndex >= 0) && (groupIndex < groupIds.length) ? groupIds[groupIndex] : 
      999999;
  }
  
  private int getArticleId(int articleIndex) {
    return (articleIndex >= 0) && (articleIndex < articleIds.length) ? articleIds[articleIndex] : 
      888888;
  }
  
  private void checkCode(String method, int expectedCode, int code) throws ProtocolViolationException
  {
    if (code != expectedCode) {
      throw new ProtocolViolationException(method, expectedCode, code);
    }
  }
  
  private void checkCondition(boolean condition, String method, String message) throws ProtocolViolationException
  {
    if (!condition) {
      throw new ProtocolViolationException(method, message);
    }
  }
}
