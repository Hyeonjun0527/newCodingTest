import java.io.*;
import java.util.*;

class Info implements Comparable<Info> {
    int size, freeze, startDate, failCount;
    String name;

  public
    Info(int size, int freeze, int startDate, int failCount, String name) {
        this.size = size;
        this.freeze = freeze;
        this.startDate = startDate;
        this.failCount = failCount;
        this.name = name;
    }

    @Override public int compareTo(Info other) {
        if (this.size != other.size)
            return other.size - this.size;
        if (this.freeze != other.freeze)
            return this.freeze - other.freeze;
        if (this.startDate != other.startDate)
            return this.startDate - other.startDate;
        if (this.failCount != other.failCount)
            return this.failCount - other.failCount;
        return this.name.compareTo(other.name);
    }
}

public class Main {
    static void changeBest(Info[] userRes, Info now) {
        if (userRes[0].size > now.size)
            return;
        else if (userRes[0].size < now.size)
            userRes[0] = now;
        else {
            if (userRes[0].freeze < now.freeze)
                return;
            else if (userRes[0].freeze > now.freeze)
                userRes[0] = now;
        }
    }

  public
    static void main(String[] args) throws IOException {
        BufferedReader br =
            new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());

        int N = Integer.parseInt(st.nextToken());
        int W = Integer.parseInt(st.nextToken());

        List<Info> res = new ArrayList<>();

        for (int ord = 0; ord < N; ord++) {
            Info[] userRes = new Info[]{new Info(0, 0, 0, 0, "None")};

            String name = br.readLine();
            userRes[0].name = name;

            String[] board = new String[7];
            for (int i = 0; i < 7; i++) {
                board[i] = br.readLine();
            }

            int size = 0;
            int freeze = 0;
            int startDate = 0;
            int dateCount = 0;

            for (int j = 0; j < W; j++) {
                for (int i = 0; i < 7; i++) {
                    char current = board[i].charAt(j);
                    if (current == 'O') {
                        if (size == 0)
                            startDate = dateCount;
                        size++;
                        changeBest(userRes, new Info(size, freeze, startDate,
                                                     userRes[0].failCount,
                                                     userRes[0].name));
                    } else if (current == 'F' && size != 0) {
                        freeze++;
                    } else if (current == 'X') {
                        userRes[0].failCount++;
                        size = 0;
                        freeze = 0;
                    }
                    dateCount++;
                }
            }
            res.add(userRes[0]);
        }

        Collections.sort(res);

        int rank = 1;
        for (int i = 0; i < res.size(); i++) {
            if (i != 0) {
                Info prev = res.get(i - 1);
                Info curr = res.get(i);
                if (curr.failCount != prev.failCount ||
                    curr.size != prev.size ||
                    curr.startDate != prev.startDate ||
                    curr.freeze != prev.freeze) {
                    rank++;
                }
            }
            System.out.println(rank + ". " + res.get(i).name);
        }
    }
}