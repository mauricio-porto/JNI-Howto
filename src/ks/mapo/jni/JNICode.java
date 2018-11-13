/**
 * 
 */
package ks.mapo.jni;

import java.io.IOException;

/**
 * @author mapo
 *
 */
public final class JNICode {

	static {
    	System.loadLibrary("JNICode");
	}

	/**
	 * 
	 */
	public JNICode() {
		super();
		registerCallback("callback", "(Ljava/lang/String;)V");
	}

	public void callback(String message) {
		System.out.println("Java received from native: " + message);
	}

	public void print(String str) {
		printNative(str);
	}

	private native void registerCallback(String methodName, String signature);
    private native void printNative(String something);
}
