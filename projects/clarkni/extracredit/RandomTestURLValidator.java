
/* ==================================================================
 * CS362 - 400 Summer 2018
 * Mui Clark
 * Description:  Random test generator for URLValidator valid method
 * Referernce:   Original UrlValidatorTest from Apache commons
 * ==================================================================
 */

import junit.framework.TestCase;
import java.util.Random;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class RandomTestURLValidator extends TestCase {

	

	private static final String[] VALID_SCHEMES = { "http", "https", "ftp" };
	private static final String[] VALID_TLDS = { "com", "edu", "org", "gov" }; // taken from DomainValidator.java
	private static final String URL_REGEX = "^(([^:/?#]+):)?(//([^/?#]*))?([^?#]*)(\\?([^#]*))?(#(.*))?"; // taken from
																											// RegexValidator.java
	private static final int NUM_TESTS = 5000; // for number of iterations

	// For test results
	
	int errorCount = 0; // error counter variable

	// random testing - will print error message if there is a mismatch between
	// actual and expected

	public void testIsValid() {

		Pattern urlPattern = Pattern.compile(URL_REGEX);
		UrlValidator urlValidator = new UrlValidator();
		String urlTest, scheme, authority;
		boolean expected;

		for (int i = 0; i < NUM_TESTS; i++) {
			urlTest = generateURLS();
			expected = true;

			Matcher urlMatcher = urlPattern.matcher(urlTest);
			while (urlMatcher.find()) {
				scheme = urlMatcher.group(1); // grouping based on details given in URLValidator.java
				authority = urlMatcher.group(3);

				expected &= isSchemeValid(scheme);

				// test authority
				if (authority == null) {
					expected = false;
				} else {
					String[] authorities = authority.split(":");
					expected &= isAuthorityValid(authorities[0]);
				}
			}
			System.out.println("URL to test: " + urlTest + " \nExpected result: " + expected);
			assertEquals(urlTest, expected, urlValidator.isValid(urlTest));
		}

	}

	public boolean isSchemeValid(String scheme) {
		if(scheme != null) {
			String temp;
			for(String str : VALID_SCHEMES) {
				if(scheme.endsWith(":")) {
					temp = scheme.substring(0,scheme.length() - 1);
					if (temp.equals(str))
						return true;
				}
			}
		}
		return false;
	}

	public boolean isAuthorityValid(String authorities) {
		if (authorities.substring(0, 2).equals("//")) {
			String[] words = authorities.substring(2, authorities.length()).split("\\.");
			if (words.length < 2) {
				return false;
			}
			for (String a: VALID_TLDS) {
				if (words[words.length-1].equals(a)) {
					return true;
				}
			}
		}
		return false;
	}

	// generate random urls

	String generateURLS() {
		Random randoms = new Random();
		final String[] schemes = { "http", "ftp", "https", " ", "hp" };
		final String[] tlds = { "edu", "gov", "org", " ", "com" };
		final String[] names = { "bing.", "", "mozilla.", "google." };
		StringBuilder stringBuilds = new StringBuilder();

		// random scheme
		if(randoms.nextInt(10)!= 0)
			stringBuilds.append(schemes[randoms.nextInt(schemes.length)]);
		
		if(randoms.nextInt(10) !=0) {
			stringBuilds.append("://");  //do not add "://" once every 10th round
			}
						
		if (randoms.nextInt(20) != 0) {
			stringBuilds.append("www."); // do not add www once every 20th round
		}
		
		stringBuilds.append(names[randoms.nextInt(names.length)]); // randomly pick a name
				
		
		stringBuilds.append(tlds[randoms.nextInt(tlds.length)]); // randomly pick a tlds

		return stringBuilds.toString();
	}
}

