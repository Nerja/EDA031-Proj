package testServer2;

import java.util.ArrayList;

class TestNewsgroup { private String title;
  private int id;
  private int index;
  private ArrayList<TestArticle> articles;
  
  public TestNewsgroup(String title) { this.title = title;
    id = -1;
    index = -1;
    articles = new ArrayList();
  }
  
  public int size() {
    return articles.size();
  }
  
  public String getTitle() {
    return title;
  }
  
  public void addArticle(TestArticle art) {
    articles.add(art);
  }
  
  public void deleteArticle(String articleTitle) {
    int i = 0;
    while ((i < articles.size()) && 
      (!((TestArticle)articles.get(i)).getTitle().equals(articleTitle))) {
      i++;
    }
    if (i < articles.size()) {
      articles.remove(i);
    }
  }
  
  public TestArticle articleAt(int i) {
    return (TestArticle)articles.get(i);
  }
  
  public int getId() {
    return id;
  }
  
  public void setId(int newId) {
    id = newId;
  }
  
  public int getIndex() {
    return index;
  }
  
  public void setIndex(int newIndex) {
    index = newIndex;
  }
}
