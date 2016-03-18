import java.util.*;

public class Main {

	public int KMP(String A , String B){
		//System.out.println(A);
		//System.out.println(B);
		int ans = 0;
		int next[] = getNext(A);
		/*
		for(int i = 0 ; i < next.length ; i ++){
			System.out.print(next[i] + " ");
		}
		System.out.println();
		*/
		int lenA = A.length();
		int lenB = B.length();
		char pa[] = A.toCharArray();
		char pb[] = B.toCharArray();

		int i = 0;
		int j = 0;
		while(j < lenB){
			//System.out.println(j+" "+i);
			if(i == -1 || pa[i] == pb[j]){
				i ++;
				j ++;
			} else {
				i = next[i];
			}
			if(i == lenA){
				ans ++;
				i = next[lenA];
			}
		}
		return ans;
	}

	public int[] getNext(String A){
		int len = A.length();
		char p[] = A.toCharArray();
		int next[] = new int[len+1];
		next[0] = -1;
		int i = 0 ; 
		int k = -1;
		while(i < len){
			//System.out.println(i + " "+k);
			if(k == -1 || p[i] == p[k]){
				next[++i] = ++k; 
			}else{
				k = next[k];
			}
		}
		return next;
	}

	public void run(){

		Scanner scan = new Scanner(System.in);
		int n = scan.nextInt();
		for(int i = 0 ; i < n ; i ++){
			String A = scan.next();
			String B = scan.next();
			int ans = KMP(A , B);
			System.out.println(ans);
		}
		
	}

	public static void main(String args[]){
		new Main().run();
	}

}