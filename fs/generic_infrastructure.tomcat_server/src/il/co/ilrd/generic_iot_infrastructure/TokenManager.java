package il.co.ilrd.generic_iot_infrastructure;

import java.io.UnsupportedEncodingException;
import java.util.Date;
import java.util.concurrent.TimeUnit;

import io.jsonwebtoken.Claims;
import io.jsonwebtoken.JwtBuilder;
import io.jsonwebtoken.Jwts;
import io.jsonwebtoken.SignatureAlgorithm;

public class TokenManager {
	static String createJWT(String email , long ttlMillis) {
		long nowMillis = System.currentTimeMillis();
		Date now = new Date(nowMillis);
		JwtBuilder builder = null;
		
		try {
			builder = Jwts.builder()
					.setIssuedAt(now)
					.setExpiration(new Date(System.currentTimeMillis() + TimeUnit.HOURS.toMillis(8)))
					.claim("email", email)
					.signWith(SignatureAlgorithm.HS256, "bigSecret".getBytes("UTF-8"));
			if (ttlMillis > 0) {
				long expMillis = nowMillis + ttlMillis;
				Date exp = new Date(expMillis);
				builder.setExpiration(exp);
			}
		} catch (UnsupportedEncodingException e) {
			e.printStackTrace();
		}
		
		return builder.compact();
	}
	
	private static Claims decodeJWT(String token) {
		Claims claims;
        try {
            claims = Jwts.parser()
            		.setSigningKey("bigSecret".getBytes("UTF-8"))
        			.parseClaimsJws(token)
                    .getBody();
        } catch (Exception e) {
            claims = null;
        }
        
        return claims;
	}
	
	public static String getEmail(String token) {
		String email = null;
		Claims claims = decodeJWT(token);
		
		if (claims != null) {
			email = (String)claims.get("email");
		}
		return email;
	}
}
