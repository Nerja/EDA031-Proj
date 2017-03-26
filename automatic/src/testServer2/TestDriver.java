package testServer2;

import common.ConnectionClosedException;

public class TestDriver {
  private ExtendedCommandHandler comHand;
  private int testNumber;
  private TestNewsarchive archive;
  
  public TestDriver(ExtendedCommandHandler comHand) {
    this.comHand = comHand;
  }
  
  public void runTests() {
    testNumber = 0;
    archive = new TestNewsarchive();
    try {
      TestNewsgroup[] groups = new TestNewsgroup[3];
      groups[0] = new TestNewsgroup("Group 1");
      groups[1] = new TestNewsgroup("Group 2");
      groups[2] = new TestNewsgroup("This is a group with a long title, but the server must be able to handle that.");
      

      TestArticle[] articles = new TestArticle[3];
      articles[0] = new TestArticle("Article 1", "Anonymous author", 
        "This is a short text");
      articles[1] = new TestArticle("Article 2", "Another author", 
        "A somewhat longer text,\ncontaining more than one line.\nTo be exact, three lines.\n");
      

      StringBuffer longText = new StringBuffer();
      for (int i = 1; i <= 50; i++) {
        longText.append("Line number " + i + " of a long text.\n");
      }
      articles[2] = new TestArticle("A long article", "A third author", 
        longText.toString());
      


      System.out.println("*** THE FOLLOWING TESTS SHOULD PASS ***");
      System.out.println();
      
      checkListGroups();
      
      checkCreateGroup(groups[0]);
      checkListGroups();
      
      checkCreateGroup(groups[1]);
      checkCreateGroup(groups[2]);
      checkListGroups();
      
      checkDeleteGroup(archive.groupAt(1));
      checkListGroups();
      


      checkListArticles(archive.groupAt(0));
      checkListArticles(archive.groupAt(1));
      
      checkCreateArticle(archive.groupAt(0), articles[0]);
      checkCreateArticle(archive.groupAt(0), articles[1]);
      System.out.println("The following test will take some time (create long article) ...");
      
      checkCreateArticle(archive.groupAt(0), articles[2]);
      checkListArticles(archive.groupAt(0));
      
      checkGetArticle(archive.groupAt(0), archive.groupAt(0).articleAt(0));
      checkGetArticle(archive.groupAt(0), archive.groupAt(0).articleAt(1));
      System.out.println("The following test will take some time (get long article) ...");
      
      checkGetArticle(archive.groupAt(0), archive.groupAt(0).articleAt(2));
      
      checkDeleteArticle(archive.groupAt(0), archive.groupAt(0)
        .articleAt(0));
      checkDeleteArticle(archive.groupAt(0), archive.groupAt(0)
        .articleAt(1));
      checkListArticles(archive.groupAt(0));
      
      checkGetArticle(archive.groupAt(0), archive.groupAt(0).articleAt(0));
      


      System.out.println("*** THE FOLLOWING TESTS SHOULD GIVE ERRORS ***");
      System.out.println();
      
      TestNewsgroup nonExistingGroup = new TestNewsgroup("Non-existing");
      TestArticle testArticle = new TestArticle("Test-article", 
        "No author", "No text");
      
      System.out.println("Create group with duplicate name ...");
      try {
        TestNewsgroup duplicateGroup = new TestNewsgroup("Group 1");
        checkCreateGroup(duplicateGroup);
        throw new FailedTestException2();
      }
      catch (FailedTestException localFailedTestException1)
      {
    	  System.out.println("Delete non-existing group ...");
        try {
          checkDeleteGroup(nonExistingGroup);
          System.out.println("... but succeeded, NOT correct!");
        }
        catch (FailedTestException localFailedTestException2) {}
        

        System.out.println("List articles of non-existing group ...");
        try {
          checkListArticles(nonExistingGroup);
          throw new FailedTestException2();
        }
        catch (FailedTestException localFailedTestException3)
        {
        	System.out.println("Create article in non-existing group ...");
          try {
            checkCreateArticle(nonExistingGroup, testArticle);
            throw new FailedTestException2();
          }
          catch (FailedTestException localFailedTestException4)
          {
        	  System.out.println("Delete article in non-existing group ...");
            try {
              checkDeleteArticle(nonExistingGroup, testArticle);
              throw new FailedTestException2();
            }
            catch (FailedTestException localFailedTestException5)
            {
            	System.out.println("Delete non-existing article in existing group ...");
              try
              {
                checkDeleteArticle(archive.groupAt(0), testArticle);
                throw new FailedTestException2();
              }
              catch (FailedTestException localFailedTestException6)
              {
            	  System.out.println("Get article in non-existing group ...");
                try {
                  checkGetArticle(nonExistingGroup, testArticle);
                  throw new FailedTestException2();
                }
                catch (FailedTestException localFailedTestException7)
                {
                	System.out.println("Get non-existing article in existing group ...");
                  try
                  {
                    checkGetArticle(archive.groupAt(0), testArticle);
                    throw new FailedTestException2();
                  }
                  catch (FailedTestException localFailedTestException8)
                  {
                	  System.out.println("*** PASSED ALL TESTS ***");
                  } } } } } } }
      return; } catch (FailedTestException e) { System.out.println("*** DID NOT PASS ALL TESTS ***");
    } catch (FailedTestException2 e) {
    	System.out.println("... but succeeded, NOT correct!");
    	System.out.println();
    	System.out.println("*** DID NOT PASS ALL TESTS ***");
    }
  }
  
  private void checkListGroups() throws TestDriver.FailedTestException {
    try {
      startTest("List groups");
      String[] receivedGroupNames = comHand.listGroups();
      if (receivedGroupNames.length != archive.size()) {
        error("Wrong number of groups. Expected " + archive.size() + 
          ", received " + receivedGroupNames.length);
      }
      int[] groupIds = comHand.getGroupIds();
      for (int i = 0; i < receivedGroupNames.length; i++) {
        String expectedGroupName = archive.groupAt(i).getTitle();
        if (receivedGroupNames[i].length() != expectedGroupName.length()) {
          error("Wrong group name length, group number " + i + ". Expected " + 
            expectedGroupName.length() + ", received " + 
            receivedGroupNames[i].length());
        }
        if (!receivedGroupNames[i].equals(expectedGroupName)) {
          error("Wrong group name, group number " + i + ". Expected " + 
            expectedGroupName + ", received " + 
            receivedGroupNames[i]);
        }
        archive.groupAt(i).setId(groupIds[i]);
        archive.groupAt(i).setIndex(i);
      }
      passedTest();
    } catch (ConnectionClosedException e) {
      connectionClosed();
    }
  }
  
  private void checkCreateGroup(TestNewsgroup group) throws TestDriver.FailedTestException
  {
    archive.addGroup(group);
    try {
      String groupName = group.getTitle();
      startTest("Create group: " + groupName);
      int errorCode = comHand.createGroup(groupName);
      if (errorCode != 0) {
        error("Could not create group: " + groupName);
      }
      passedTest();
    } catch (ConnectionClosedException e) {
      connectionClosed();
    }
  }
  
  private void checkDeleteGroup(TestNewsgroup group) throws TestDriver.FailedTestException
  {
    archive.deleteGroup(group.getTitle());
    try {
      String groupName = group.getTitle();
      startTest("Delete group: " + groupName);
      int errorCode = comHand.deleteGroup(group.getIndex());
      if (errorCode != 0) {
        error("Could not delete group: " + groupName);
      }
      passedTest();
    } catch (ConnectionClosedException e) {
      connectionClosed();
    }
  }
  
  private void checkListArticles(TestNewsgroup group) throws TestDriver.FailedTestException
  {
    try {
      String groupName = group.getTitle();
      startTest("List articles, group: " + groupName);
      String[] receivedArticleNames = comHand.listArticles(group
        .getIndex());
      if (receivedArticleNames == null) {
        error("Group does not exist: " + groupName);
      }
      if (receivedArticleNames.length != group.size()) {
        error("Wrong number of articles. Expected " + group.size() + 
          ", received " + receivedArticleNames.length);
      }
      int[] articleIds = comHand.getArticleIds();
      for (int i = 0; i < receivedArticleNames.length; i++) {
        String expectedArticleName = group.articleAt(i).getTitle();
        if (!receivedArticleNames[i].equals(expectedArticleName)) {
          error("Wrong article name, article number " + i + 
            ". Expected " + expectedArticleName + 
            ", received " + receivedArticleNames[i]);
        }
        group.articleAt(i).setId(articleIds[i]);
        group.articleAt(i).setIndex(i);
      }
      passedTest();
    } catch (ConnectionClosedException e) {
      connectionClosed();
    }
  }
  
  private void checkCreateArticle(TestNewsgroup group, TestArticle article) throws TestDriver.FailedTestException
  {
    group.addArticle(article);
    try {
      String groupName = group.getTitle();
      String articleName = article.getTitle();
      startTest("Create article: " + articleName + ", in group: " + 
        groupName);
      int errorCode = comHand.createArticle(group.getIndex(), 
        articleName, article.getAuthor(), article.getText());
      if (errorCode != 0) {
        error("Could not create article: " + articleName);
      }
      passedTest();
    } catch (ConnectionClosedException e) {
      connectionClosed();
    }
  }
  
  private void checkDeleteArticle(TestNewsgroup group, TestArticle article) throws TestDriver.FailedTestException
  {
    group.deleteArticle(article.getTitle());
    try {
      String groupName = group.getTitle();
      String articleName = article.getTitle();
      startTest("Delete article: " + articleName + ", in group: " + 
        groupName);
      int errorCode = comHand.deleteArticle(group.getIndex(), article
        .getIndex());
      if (errorCode != 0) {
        error("Could not delete article: " + articleName);
      }
      passedTest();
    } catch (ConnectionClosedException e) {
      connectionClosed();
    }
  }
  
  private void checkGetArticle(TestNewsgroup group, TestArticle article) throws TestDriver.FailedTestException
  {
    try {
      String groupName = group.getTitle();
      String articleName = article.getTitle();
      startTest("Get article: " + articleName + ", in group: " + 
        groupName);
      String[] receivedArticleContents = comHand.getArticle(group
        .getIndex(), article.getIndex());
      if (receivedArticleContents.length != 3)
        error("Could not get article:" + articleName);
      if (!receivedArticleContents[0].equals(article.getTitle())) {
        error("Article title incorrect. Received: " + 
          receivedArticleContents[0] + ", expected: " + 
          article.getTitle());
      }
      if (!receivedArticleContents[1].equals(article.getAuthor())) {
        error("Article author incorrect. Received: " + 
          receivedArticleContents[1] + ", expected: " + 
          article.getAuthor());
      }
      if (!receivedArticleContents[2].equals(article.getText())) {
        error("Article text incorrect. Received: " + 
          receivedArticleContents[2] + ", expected: " + 
          article.getText());
      }
      passedTest();
    } catch (ConnectionClosedException e) {
      connectionClosed();
    }
  }
  
  private void startTest(String msg) {
    testNumber += 1;
    System.out.println("*** Start test number " + testNumber + ". " + msg);
  }
  
  private void passedTest() {
	  System.out.println("*** ... passed");
	  System.out.println();
  }
  
  private void connectionClosed() throws TestDriver.FailedTestException {
    error("Server closed connection");
  }
  
  private void error(String msg) throws TestDriver.FailedTestException {
	  System.out.println("*** ERROR: " + msg);
	  System.out.println();
    throw new FailedTestException();
  }
  
  class FailedTestException
    extends Exception
  {
    private static final long serialVersionUID = 1L;
    
    FailedTestException() {}
  }
  
  class FailedTestException2
    extends Exception
  {
    private static final long serialVersionUID = 1L;
    
    FailedTestException2() {}
  }
}
