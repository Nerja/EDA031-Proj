package testServer2;

import java.util.ArrayList;

class TestNewsarchive { private ArrayList<TestNewsgroup> groups;
  
  public TestNewsarchive() { groups = new ArrayList(); }
  
  public int size()
  {
    return groups.size();
  }
  
  public void addGroup(TestNewsgroup group) {
    groups.add(group);
  }
  
  public void deleteGroup(String groupTitle) {
    int i = 0;
    while ((i < groups.size()) && 
      (!((TestNewsgroup)groups.get(i)).getTitle().equals(groupTitle))) {
      i++;
    }
    if (i < groups.size()) {
      groups.remove(i);
    }
  }
  
  public TestNewsgroup groupAt(int i) {
    return (TestNewsgroup)groups.get(i);
  }
}
