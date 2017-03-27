package testServer2;

import common.MessageHandler;

public class ExtendedCommandHandler extends common.CommandHandler
{
  public ExtendedCommandHandler(MessageHandler mh) {
    super(mh);
  }
  
  public int[] getGroupIds() {
    return groupIds;
  }
  
  public int[] getArticleIds() {
    return articleIds;
  }
}
