package il.co.ilrd.generic_iot_infrastructure;

import java.math.BigInteger;
import java.security.NoSuchAlgorithmException;
import java.security.SecureRandom;
import java.security.spec.InvalidKeySpecException;

import javax.crypto.SecretKeyFactory;
import javax.crypto.spec.PBEKeySpec;

public class PasswordEncryptor {
	/**
	 * A utility class to hash passwords and check passwords vs hashed values. It uses a combination of hashing and unique
	 * salt. The algorithm used is PBKDF2WithHmacSHA1 which, although not the best for hashing password (vs. bcrypt) is
	 * still considered robust and <a href="https://security.stackexchange.com/a/6415/12614"> recommended by NIST </a>.
	 * The hashed value has 256 bits.
	 */


	/**
	 * static utility class
	 */
	private PasswordEncryptor() { }

	/**
	 * Returns a salted and hashed password using the provided hash.<br>
	 * Note - side effect: the password is destroyed (the char[] is filled with zeros)
	 *
	 * @param password the password to be hashed
	 * @param salt     a 16 bytes salt, ideally obtained with the getNextSalt method
	 *
	 * @return the hashed password with a pinch of salt
	 */
	static String generateStorngPasswordHash(String password) {
		int iterations = 1000;
		char[] chars = password.toCharArray();
		byte[] salt = null;
		byte[] hash = null;
		
		try {
			salt = getSalt();
			PBEKeySpec spec = new PBEKeySpec(chars, salt, iterations, 64 * 8);
			SecretKeyFactory skf = SecretKeyFactory.getInstance("PBKDF2WithHmacSHA1");
			hash = skf.generateSecret(spec).getEncoded();
			
			return iterations + ":" + toHex(salt) + ":" + toHex(hash);
		} catch (NoSuchAlgorithmException | InvalidKeySpecException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return null;
	}
	
	/**
	 * Returns a random salt to be used to hash a password.
	 *
	 * @return a 16 bytes random salt
	 */
	private static byte[] getSalt() throws NoSuchAlgorithmException {
		SecureRandom sr = SecureRandom.getInstance("SHA1PRNG");
		byte[] salt = new byte[16];
		sr.nextBytes(salt);
		return salt;
	}

	private static String toHex(byte[] array) throws NoSuchAlgorithmException {
		BigInteger bi = new BigInteger(1, array);
		String hex = bi.toString(16);
		int paddingLength = (array.length * 2) - hex.length();
		if(paddingLength > 0)
		{
			return String.format("%0"  +paddingLength + "d", 0) + hex;
		}else{
			return hex;
		}
	}
	
	/**
	 * Returns true if the given password match the hashed value, false otherwise.<br>
	 * Note - side effect: the password is destroyed (the char[] is filled with zeros)
	 *
	 * @param password     the password to check
	 * @param salt         the salt used to hash the password
	 * @param expectedHash the expected hashed value of the password
	 *
	 * @return true if the given password and salt match the hashed value, false otherwise
	 */

	static boolean validatePassword(String originalPassword, String storedPassword) {
		String[] parts = storedPassword.split(":");
		int iterations = Integer.parseInt(parts[0]);
		int diff = -1;
		byte[] salt;
		try {
			salt = fromHex(parts[1]);
			byte[] hash = fromHex(parts[2]);

			PBEKeySpec spec = new PBEKeySpec(originalPassword.toCharArray(), salt, iterations, hash.length * 8);
			SecretKeyFactory skf = SecretKeyFactory.getInstance("PBKDF2WithHmacSHA1");
			byte[] testHash = skf.generateSecret(spec).getEncoded();
			diff = hash.length ^ testHash.length;
			for(int i = 0; i < hash.length && i < testHash.length; i++)
			{
				diff |= hash[i] ^ testHash[i];
			}
		} catch (NoSuchAlgorithmException | InvalidKeySpecException e) {
			e.printStackTrace();
		}

		return diff == 0;
	}
	
	public static byte[] fromHex(String hex) throws NoSuchAlgorithmException {
		byte[] bytes = new byte[hex.length() / 2];
		for(int i = 0; i<bytes.length ;i++)
		{
			bytes[i] = (byte)Integer.parseInt(hex.substring(2 * i, 2 * i + 2), 16);
		}
		return bytes;
	}
}
