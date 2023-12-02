public class Gibaus 
{

    public static void main(String[] args) 
    {

        System.out.println("Gibaus Java Edition");

        Thread[] newthreads = new Thread[6];

        for (int i = 0; i < 6; i++) 
        {
            final char threadChar = (char) ('A' + i);
            newthreads[i] = new Thread(() -> printCharacters(threadChar));
            newthreads[i].start();
        }
        for (int i = 0; i < 6; i++) 
        {
            try
            {
                newthreads[i].join();
            }
            catch (InterruptedException e) 
            {
                e.printStackTrace();
            }            
        }
    }

    private static void printCharacters(char ch) 
    {
        for (int i = 0; i < 5; i++) 
        {
            for (int j = 0; j < 10; j++) 
            {
                System.out.print(ch);
            }
            System.out.println();
            try
            {
                Thread.sleep((long) (Math.random() * 400) + 100);
            }
            catch (InterruptedException e) 
            {
                e.printStackTrace();
            }   
        }
    }
}

