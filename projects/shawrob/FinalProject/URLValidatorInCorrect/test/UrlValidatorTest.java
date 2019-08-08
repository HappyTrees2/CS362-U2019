/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
/*****************************************************/
import java.util.Random;
import org.junit.Test;
/****************************************************/

import junit.framework.TestCase;

/**
 * Performs Validation Test for url validations.
 *
 * @version $Revision$
 */
public class UrlValidatorTest extends TestCase {

   private final boolean printStatus = false;
   private final boolean printIndex = false;//print index that indicates current scheme,host,port,path, query test were using.

   /********************************************************************************************/
   //Variables used to create good and bad URLs
   String[] goodSchemes = new String[] {"https://", "http://", "ftp://"};
   String[] badSchemes = new String[] {"://", "", "http:/"}; 
   String[] goodAuthor = new String[] {"www.amazon.com", "108.174.10.10", "amazon.bd",};
   String[] badAuthor = new String[] {"wwhe.sin", "500.300.255.34", "amazon",};;
   String[] goodPorts = new String[] {":80", ":32102", ""};
   String[] badPorts = new String[] {":000-00", ":9re999", ":3f3f3"};
   String[] goodPaths = new String[] {"/imbd", "/jot", "/test"};
   String[] badPaths = new String[] {"/imbd", "/jot", "/test"};
   String[] goodQue = new String[] {"", "s?=", "?action="};
   String[] badQue = new String[] {"zzzzz", "s?zsasda", "?tion", "???"};
   /********************************************************************************************/
   
   
   public UrlValidatorTest(String testName) {
      super(testName);
   }

   @Override
protected void setUp() {
      for (int index = 0; index < testPartsIndex.length - 1; index++) {
         testPartsIndex[index] = 0;
      }
   }
   
   /***********************************************************************************/
   //UNIT TESTING OF 100 DIFFERENT URLS
   //to get random number for the different values
   public static String getUrlVal(Random num, String[] line)
   {
	   int spot = num.nextInt(line.length);
	   return line[spot];
   }
   
   //Pull 100 randomly generated lines of a file
   @Test
   public void testIsValid01() {
	   System.out.println("Unit Testing Correct Urls");

	   Random positiveNum = new Random(3);
	   //Read in the urls that should be true
	   for(int i = 0; i < 50; i++)
	   {
		   String Scem = getUrlVal(positiveNum, goodSchemes);
		   String Auth = getUrlVal(positiveNum, goodAuthor);
		   String Port = getUrlVal(positiveNum, goodPorts);
		   String Path = getUrlVal(positiveNum, goodPaths);
		   String Queu = getUrlVal(positiveNum, goodQue);
		   
		   //Put all vals together
		   String theUrl = Scem + Auth + Port + Path + Queu;
		   //Goes through and shows what is invalid or not
		   UrlValidator urlVal = new UrlValidator();
		   if(urlVal.isValid(theUrl)==false)
			   System.out.println(theUrl + " Incorrect Scheme: " + Scem);
		   if(urlVal.isValid(theUrl)==false)
			   System.out.println(theUrl + " Incorrect Authority: " + Auth);
		   if(urlVal.isValid(theUrl)==false)
			   System.out.println(theUrl + " Incorrect Path: " + Path);
		   if(urlVal.isValid(theUrl)==false)
			   System.out.println(theUrl + " Incorrect Query: " + Queu);
		   
	   }
	   System.out.println("\n\nUnit Testing Bad Urls\n\n");
	   
	   for(int i = 0; i < 15; i++) // -Checking Schemas
	   {
		   String Scem = getUrlVal(positiveNum, badSchemes);
		   String Auth = getUrlVal(positiveNum, goodAuthor);
		   String Port = getUrlVal(positiveNum, goodPorts);
		   String Path = getUrlVal(positiveNum, goodPaths);
		   String Queu = getUrlVal(positiveNum, goodQue);

		   //Prints out the screen the correct values that they should be
		   UrlValidator urlVal = new UrlValidator();
		   String theUrl = Scem + Auth + Port + Path + Queu;
		   if(urlVal.isValid(theUrl)==true) //Strange error 
			   System.out.println(theUrl + " Correct Scheme: " + Scem); 
	   }
	   
	   for(int i = 0; i < 15; i++) //Checking the Authority
	   {
		   String Scem = getUrlVal(positiveNum, goodSchemes);
		   String Auth = getUrlVal(positiveNum, badAuthor);
		   String Port = getUrlVal(positiveNum, goodPorts);
		   String Path = getUrlVal(positiveNum, goodPaths);
		   String Queu = getUrlVal(positiveNum, goodQue);
		   
		   UrlValidator urlVal = new UrlValidator();
		   String theUrl = Scem + Auth + Port + Path + Queu;
		   if(urlVal.isValid(theUrl)==true) //Strange error 
			   System.out.println(theUrl + " Correct Authority: " + Auth);
	   }
	   
	   for(int i = 0; i < 15; i++) //checking the path
	   {
		   String Scem = getUrlVal(positiveNum, goodSchemes);
		   String Auth = getUrlVal(positiveNum, goodAuthor);
		   String Port = getUrlVal(positiveNum, goodPorts);
		   String Path = getUrlVal(positiveNum, badPaths);
		   String Queu = getUrlVal(positiveNum, goodQue);
		   
		   UrlValidator urlVal = new UrlValidator();
		   String theUrl = Scem + Auth + Port + Path + Queu;
		   if(urlVal.isValid(theUrl)==false)
			   System.out.println(theUrl + " Correct Path: " + Path);
	   }
	   
	   for(int i = 0; i < 15; i++) //checking the Query
	   {
		   String Scem = getUrlVal(positiveNum, goodSchemes);
		   String Auth = getUrlVal(positiveNum, goodAuthor);
		   String Port = getUrlVal(positiveNum, goodPorts);
		   String Path = getUrlVal(positiveNum, goodPaths);
		   String Queu = getUrlVal(positiveNum, badQue);
		   
		   UrlValidator urlVal = new UrlValidator();
		   String theUrl = Scem + Auth + Port + Path + Queu;
		   if(urlVal.isValid(theUrl)==false)
			   System.out.println(theUrl + " Correct Query: " + Queu);
		   
	   }

	   System.out.println("Unit Testing Ends");
   }
   /****************************************************************************************/
   

   public void testIsValid() {
        testIsValid(testUrlParts, UrlValidator.ALLOW_ALL_SCHEMES);
        setUp();
        long options =
            UrlValidator.ALLOW_2_SLASHES
                + UrlValidator.ALLOW_ALL_SCHEMES
                + UrlValidator.NO_FRAGMENTS;

        testIsValid(testUrlPartsOptions, options);
   }

   public void testIsValidScheme() {
      if (printStatus) {
         System.out.print("\n testIsValidScheme() ");
      }
      //UrlValidator urlVal = new UrlValidator(schemes,false,false,false);
      UrlValidator urlVal = new UrlValidator(schemes, 0);
      for (int sIndex = 0; sIndex < testScheme.length; sIndex++) {
         ResultPair testPair = testScheme[sIndex];
         boolean result = urlVal.isValidScheme(testPair.item);
         assertEquals(testPair.item, testPair.valid, result);
         if (printStatus) {
            if (result == testPair.valid) {
               System.out.print('.');
            } else {
               System.out.print('X');
            }
         }
      }
      if (printStatus) {
         System.out.println();
      }

   }

   /**
    * Create set of tests by taking the testUrlXXX arrays and
    * running through all possible permutations of their combinations.
    *
    * @param testObjects Used to create a url.
    */
   public void testIsValid(Object[] testObjects, long options) {
      UrlValidator urlVal = new UrlValidator(null, null, options);
      assertTrue(urlVal.isValid("http://www.google.com"));
      assertTrue(urlVal.isValid("http://www.google.com/"));
      int statusPerLine = 60;
      int printed = 0;
      if (printIndex)  {
         statusPerLine = 6;
      }
      do {
          StringBuilder testBuffer = new StringBuilder();
         boolean expected = true;
         for (int testPartsIndexIndex = 0; testPartsIndexIndex < testPartsIndex.length; ++testPartsIndexIndex) {
            int index = testPartsIndex[testPartsIndexIndex];
            ResultPair[] part = (ResultPair[]) testObjects[testPartsIndexIndex];
            testBuffer.append(part[index].item);
            expected &= part[index].valid;
         }
         String url = testBuffer.toString();
         boolean result = urlVal.isValid(url);
         assertEquals(url, expected, result);
         if (printStatus) {
            if (printIndex) {
               System.out.print(testPartsIndextoString());
            } else {
               if (result == expected) {
                  System.out.print('.');
               } else {
                  System.out.print('X');
               }
            }
            printed++;
            if (printed == statusPerLine) {
               System.out.println();
               printed = 0;
            }
         }
      } while (incrementTestPartsIndex(testPartsIndex, testObjects));
      if (printStatus) {
         System.out.println();
      }
   }


    static boolean incrementTestPartsIndex(int[] testPartsIndex, Object[] testParts) {
      boolean carry = true;  //add 1 to lowest order part.
      boolean maxIndex = true;
      for (int testPartsIndexIndex = testPartsIndex.length - 1; testPartsIndexIndex >= 0; --testPartsIndexIndex) {
         int index = testPartsIndex[testPartsIndexIndex];
         ResultPair[] part = (ResultPair[]) testParts[testPartsIndexIndex];
         maxIndex &= (index == (part.length - 1));
         if (carry) {
            if (index < part.length - 1) {
               index++;
               testPartsIndex[testPartsIndexIndex] = index;
               carry = false;
            } else {
               testPartsIndex[testPartsIndexIndex] = 0;
               carry = true;
            }
         }
      }


      return (!maxIndex);
   }

   private String testPartsIndextoString() {
       StringBuilder carryMsg = new StringBuilder("{");
      for (int testPartsIndexIndex = 0; testPartsIndexIndex < testPartsIndex.length; ++testPartsIndexIndex) {
         carryMsg.append(testPartsIndex[testPartsIndexIndex]);
         if (testPartsIndexIndex < testPartsIndex.length - 1) {
            carryMsg.append(',');
         } else {
            carryMsg.append('}');
         }
      }
      return carryMsg.toString();

   }

   public void testValidateUrl() {
      assertTrue(true);
   }

   

   

   

   //-------------------- Test data for creating a composite URL
   /**
    * The data given below approximates the 4 parts of a URL
    * <scheme>://<authority><path>?<query> except that the port number
    * is broken out of authority to increase the number of permutations.
    * A complete URL is composed of a scheme+authority+port+path+query,
    * all of which must be individually valid for the entire URL to be considered
    * valid.
    */
   ResultPair[] testUrlScheme = {new ResultPair("http://", true),
                               new ResultPair("ftp://", true),
                               new ResultPair("h3t://", true),
                               new ResultPair("3ht://", false),
                               new ResultPair("http:/", false),
                               new ResultPair("http:", false),
                               new ResultPair("http/", false),
                               new ResultPair("://", false)};

   ResultPair[] testUrlAuthority = {new ResultPair("www.google.com", true),
                                  new ResultPair("www.google.com.", true),
                                  new ResultPair("go.com", true),
                                  new ResultPair("go.au", true),
                                  new ResultPair("0.0.0.0", true),
                                  new ResultPair("255.255.255.255", true),
                                  new ResultPair("256.256.256.256", false),
                                  new ResultPair("255.com", true),
                                  new ResultPair("1.2.3.4.5", false),
                                  new ResultPair("1.2.3.4.", false),
                                  new ResultPair("1.2.3", false),
                                  new ResultPair(".1.2.3.4", false),
                                  new ResultPair("go.a", false),
                                  new ResultPair("go.a1a", false),
                                  new ResultPair("go.cc", true),
                                  new ResultPair("go.1aa", false),
                                  new ResultPair("aaa.", false),
                                  new ResultPair(".aaa", false),
                                  new ResultPair("aaa", false),
                                  new ResultPair("", false)
   };
   ResultPair[] testUrlPort = {new ResultPair(":80", true),
                             new ResultPair(":65535", true), // max possible
                             new ResultPair(":65536", false), // max possible +1
                             new ResultPair(":0", true),
                             new ResultPair("", true),
                             new ResultPair(":-1", false),
                             new ResultPair(":65636", false),
                             new ResultPair(":999999999999999999", false),
                             new ResultPair(":65a", false)
   };
   ResultPair[] testPath = {new ResultPair("/test1", true),
                          new ResultPair("/t123", true),
                          new ResultPair("/$23", true),
                          new ResultPair("/..", false),
                          new ResultPair("/../", false),
                          new ResultPair("/test1/", true),
                          new ResultPair("", true),
                          new ResultPair("/test1/file", true),
                          new ResultPair("/..//file", false),
                          new ResultPair("/test1//file", false)
   };
   //Test allow2slash, noFragment
   ResultPair[] testUrlPathOptions = {new ResultPair("/test1", true),
                                    new ResultPair("/t123", true),
                                    new ResultPair("/$23", true),
                                    new ResultPair("/..", false),
                                    new ResultPair("/../", false),
                                    new ResultPair("/test1/", true),
                                    new ResultPair("/#", false),
                                    new ResultPair("", true),
                                    new ResultPair("/test1/file", true),
                                    new ResultPair("/t123/file", true),
                                    new ResultPair("/$23/file", true),
                                    new ResultPair("/../file", false),
                                    new ResultPair("/..//file", false),
                                    new ResultPair("/test1//file", true),
                                    new ResultPair("/#/file", false)
   };

   ResultPair[] testUrlQuery = {new ResultPair("?action=view", true),
                              new ResultPair("?action=edit&mode=up", true),
                              new ResultPair("", true)
   };

   Object[] testUrlParts = {testUrlScheme, testUrlAuthority, testUrlPort, testPath, testUrlQuery};
   Object[] testUrlPartsOptions = {testUrlScheme, testUrlAuthority, testUrlPort, testUrlPathOptions, testUrlQuery};
   int[] testPartsIndex = {0, 0, 0, 0, 0};

   //---------------- Test data for individual url parts ----------------
   private final String[] schemes = {"http", "gopher", "g0-To+.",
                                      "not_valid" // TODO this will need to be dropped if the ctor validates schemes
                                    };

   ResultPair[] testScheme = {new ResultPair("http", true),
                            new ResultPair("ftp", false),
                            new ResultPair("httpd", false),
                            new ResultPair("gopher", true),
                            new ResultPair("g0-to+.", true),
                            new ResultPair("not_valid", false), // underscore not allowed
                            new ResultPair("HtTp", true),
                            new ResultPair("telnet", false)};


}
