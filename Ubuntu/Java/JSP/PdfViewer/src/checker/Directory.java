package checker;

import java.io.*;
import java.util.HashMap;
import java.util.Map;

public class Directory 
{
	public static Map<String,String> PDFS = new HashMap<String,String>();
	//static Map <String,String> PDFS = new HashMap<String,String>();
	public static void listDirectory(String dirPath, int level) 
	{
		File dir = new File(dirPath);
        File[] firstLevelFiles = dir.listFiles();
        if (firstLevelFiles != null && firstLevelFiles.length > 0) {
            for (File aFile : firstLevelFiles) {
                /*
            	for (int i = 0; i < level; i++) {
                    System.out.print("\t");
                }
                */
                if (aFile.isDirectory()) {
                	//System.out.println("[" + aFile.getName() + "]");
                    listDirectory(aFile.getAbsolutePath(), level + 1);
                  //System.out.println(level);
                } else {
           		 	if(aFile.toString().endsWith(".pdf"))
           		 	{
           		 		PDFS.put(aFile.getName(),(aFile.getAbsoluteFile()).toString());
           		 		//System.out.println(aFile.getName());
           		 	}	
           		}
            }
        }
    }
	/*
	public static void main(String[] args) {
		
		Directory.listDirectory("/home/ubuntu/Downloads/Books", 0);
		
		
		for(Map.Entry m:Directory.PDFS.entrySet())
		{  
				for(int i=0;i<4;i++)
				{
					System.out.println(m.getKey()+"----> "+m.getValue());
				}
				System.out.println("------------------------------------------------------------------");
		}  
	}
	*/
}