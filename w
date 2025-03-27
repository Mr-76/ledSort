import java.io.*;
import java.util.concurrent.*;
import java.util.ArrayList;
import java.util.concurrent.atomic.AtomicInteger;

public class ContadorPalavras {
    public static void main(String[] args) throws IOException, InterruptedException, ExecutionException {
        System.out.println("Lab8");
        Semaphore mutex = new Semaphore(1);

        ArrayList<Thread> arrayThreads = new ArrayList<Thread>();
        Integer soma = 0 ;

        ExecutorService executorService = Executors.newFixedThreadPool(args.length);
        //ExecutorService executorService = Executors.newSingleThreadExecutor();

        ArrayList<Future<Integer>> futress = new ArrayList<Future<Integer>>();

        for (int i = 0 ;i<args.length;i++){
            int finalI = i;
            Callable<Integer> tarefa = () -> {
                int soma1 = (contarPalavras(args[finalI]));
                return soma1;
            };
            Future<Integer> resultado = executorService.submit(tarefa);
            futress.add(resultado);
        }



        for (int i = 0 ; i < args.length;i ++){
            soma += futress.get(i).get();
        }


        executorService.shutdown();

        System.out.println(soma);
    }




    static int contarPalavras(String nomeArquivo) throws IOException {
        BufferedReader br = new BufferedReader(new FileReader(nomeArquivo));
        int count = 0;
        String linha;
        while ((linha = br.readLine()) != null) {
            count += linha.split("\\s+").length;
        }
        br.close();
        return count;
    }
}






