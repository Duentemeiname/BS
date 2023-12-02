import java.util.concurrent.atomic.AtomicInteger;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class Zwergenbaeckerei {

    private static final Lock backstubeSchloss = new ReentrantLock();
    private static final Condition vorratAufgebraucht = backstubeSchloss.newCondition();
    private static final Condition vorratAufgefuehrt = backstubeSchloss.newCondition();

    private static final AtomicInteger mahlVorrat = new AtomicInteger(0);
    private static final AtomicInteger eiVorrat = new AtomicInteger(0);
    private static final AtomicInteger milchVorrat = new AtomicInteger(0);

    private static void mahlAnliefern() {
        backstubeSchloss.lock();
        try {
            System.out.println("\t Mehl-Zwerg: Vor der Backstube, schlafe");
            while (mahlVorrat.get() >= 3) {
                System.out.println("\t Mehl-Zwerg: Vorrat aufgefüllt, schlafe");
                vorratAufgebraucht.await();
            }

            System.out.println("\t Mehl-Zwerg: Betrete die Backstube");
            mahlVorrat.incrementAndGet();
            System.out.println("\t Mehl-Zwerg: Anliefern (Vorrat: " + mahlVorrat + ")");
            vorratAufgefuehrt.signal();
        } catch (InterruptedException e) {
            e.printStackTrace();
        } finally {
            backstubeSchloss.unlock();
        }
    }

    private static void eiAnliefern() {
        backstubeSchloss.lock();
        try {
            System.out.println("\t\t Ei-Zwerg: Vor der Backstube, schlafe");
            while (eiVorrat.get() >= 3) {
                System.out.println("\t\t Ei-Zwerg: Vorrat aufgefüllt, schlafe");
                vorratAufgebraucht.await();
            }

            System.out.println("\t\t Ei-Zwerg: Betrete die Backstube");
            eiVorrat.incrementAndGet();
            System.out.println("\t\t Ei-Zwerg: Anliefern (Vorrat: " + eiVorrat + ")");
            vorratAufgefuehrt.signal();
        } catch (InterruptedException e) {
            e.printStackTrace();
        } finally {
            backstubeSchloss.unlock();
        }
    }

    private static void milchAnliefern() {
        backstubeSchloss.lock();
        try {
            System.out.println("\t\t\t Milch-Zwerg: Vor der Backstube, schlafe");
            while (milchVorrat.get() >= 3) {
                System.out.println("\t\t\t Milch-Zwerg: Vorrat aufgefüllt, schlafe");
                vorratAufgebraucht.await();
            }

            System.out.println("\t\t\t Milch-Zwerg: Betrete die Backstube");
            milchVorrat.incrementAndGet();
            System.out.println("\t\t\t Milch-Zwerg: Anliefern (Vorrat: " + milchVorrat + ")");
            vorratAufgefuehrt.signal();
        } catch (InterruptedException e) {
            e.printStackTrace();
        } finally {
            backstubeSchloss.unlock();
        }
    }

    private static void backen() {
        backstubeSchloss.lock();
        try {
            System.out.println("Bäckermeister: Vor der Backstube, schlafe");
            while (mahlVorrat.get() < 3 || eiVorrat.get() < 3 || milchVorrat.get() < 3) {
                System.out.println("Bäckermeister: Warte auf Zutaten, schlafe");
                vorratAufgefuehrt.await();
            }

            System.out.println("Bäckermeister: Betrete die Backstube");
            System.out.println("Bäckermeister: Backen (Vorrat: " + mahlVorrat + ", " + eiVorrat + ", " + milchVorrat + ")");
            Thread.sleep(5 * 1000);
            System.out.println("Bäckermeister: Backen fertig");

            mahlVorrat.set(0);
            eiVorrat.set(0);
            milchVorrat.set(0);

            System.out.println("Bäckermeister: Vorrat aufgebraucht, wecke Zwerge");
            vorratAufgebraucht.signalAll();
        } catch (InterruptedException e) {
            e.printStackTrace();
        } finally {
            backstubeSchloss.unlock();
        }
    }

    public static void main(String[] args) {
        System.out.println("Zwergenbäckerei Java Edition");

        for (int i = 0; i < 10; i++) {
            Thread mahlThread = new Thread(() -> {
                for (int j = 0; j < 3; j++) {
                    mahlAnliefern();
                }
            });

            Thread eiThread = new Thread(() -> {
                for (int j = 0; j < 3; j++) {
                    eiAnliefern();
                }
            });

            Thread milchThread = new Thread(() -> {
                for (int j = 0; j < 3; j++) {
                    milchAnliefern();
                }
            });

            Thread backenThread = new Thread(() -> backen());

            mahlThread.start();
            eiThread.start();
            milchThread.start();
            backenThread.start();

            try {
                mahlThread.join();
                eiThread.join();
                milchThread.join();
                backenThread.join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}
