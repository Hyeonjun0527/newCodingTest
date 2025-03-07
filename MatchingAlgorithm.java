import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;
import java.util.Random;

public class MatchingAlgorithm {

    static int CLUSTER_COUNT = 3;
    static int CPD_CANDIDATE_COUNT = 5;

    // 후보자 정보를 저장하는 클래스
    static class Candidate implements Comparable<Candidate> {
        int id;
        double rating;
        int studyField;
        int preferredTime;

        public Candidate(int id, double rating, int studyField, int preferredTime) {
            this.id = id;
            this.rating = rating;
            this.studyField = studyField;
            this.preferredTime = preferredTime;
        }

        @Override
        public int compareTo(Candidate other) {
            // rating을 기준으로 내림차순 정렬
            return Double.compare(other.rating, this.rating);
        }

        @Override
        public String toString() {
            return String.format("Candidate{id=%d, rating=%.1f, field=%d, time=%d}",
                    id, rating, studyField, preferredTime);
        }
    }

    // 두 후보자 간의 가중치를 적용한 거리 계산 함수
    private static double weightedDistance(Candidate a, Candidate b) {
        double dr = (a.rating - b.rating) * 8; // rating 차이에 가중치 8
        double df = (a.studyField - b.studyField) * 1; // studyField 차이에 가중치 1
        double dt = (a.preferredTime - b.preferredTime) * 1; // preferredTime 차이 가중치 1
        // 유클리드 거리 계산
        return Math.sqrt(dr * dr + df * df + dt * dt);
    }

    // K-means 클러스터링 수행 함수
    private static List<List<Candidate>> clusterCandidates(List<Candidate> candidates, int K) {
        int n = candidates.size();
        // 초기 센트로이드 선택: 처음 K명의 후보자 위치를 사용 (간단한 초기화)
        List<Candidate> centroids = new ArrayList<>();
        for (int i = 0; i < K; i++) {
            centroids.add(candidates.get(i));
        }

        List<Integer> assignment = new ArrayList<>(Collections.nCopies(n, -1));
        boolean changed;
        int maxIterations = 100;
        for (int iter = 0; iter < maxIterations; iter++) {
            changed = false;
            // 각 클러스터 그룹 초기화
            List<List<Candidate>> clusters = new ArrayList<>();
            for (int k = 0; k < K; k++)
                clusters.add(new ArrayList<>());

            // 각 후보자를 가장 가까운 센트로이드에 할당
            for (int i = 0; i < n; i++) {
                Candidate cand = candidates.get(i);
                double minDist = Double.MAX_VALUE;
                int closestCluster = -1;
                for (int k = 0; k < K; k++) {
                    double dist = weightedDistance(cand, centroids.get(k));
                    if (dist < minDist) {
                        minDist = dist;
                        closestCluster = k;
                    }
                }
                clusters.get(closestCluster).add(cand);
                if (assignment.get(i) != closestCluster) {
                    assignment.set(i, closestCluster);
                    changed = true;
                }
            }

            // 센트로이드 값 업데이트 (각 클러스터의 평균값)
            for (int k = 0; k < K; k++) {
                if (clusters.get(k).isEmpty())
                    continue; // 빈 클러스터 처리
                double sumRating = 0, sumField = 0, sumTime = 0;
                for (Candidate c : clusters.get(k)) {
                    sumRating += c.rating;
                    sumField += c.studyField;
                    sumTime += c.preferredTime;
                }
                int clusterSize = clusters.get(k).size();
                // 평균으로 새로운 센트로이드 계산
                double avgRating = sumRating / clusterSize;
                double avgField = sumField / clusterSize;
                double avgTime = sumTime / clusterSize;
                centroids.set(k, new Candidate(-1, avgRating, (int) Math.round(avgField), (int) Math.round(avgTime)));
            }

            if (!changed) { // 할당 변화가 없으면 수렴
                break;
            }
        }
        // 최종 클러스터 목록 반환
        // (centroids 리스트의 순서에 따라 0번 클러스터, 1번 클러스터, ...)
        // assignment 리스트나 clusters 리스트를 이용해 최종 결과를 얻음
        List<List<Candidate>> finalClusters = new ArrayList<>();
        for (int k = 0; k < K; k++) {
            finalClusters.add(new ArrayList<>());
        }
        for (int i = 0; i < n; i++) {
            int clusterIdx = assignment.get(i);
            finalClusters.get(clusterIdx).add(candidates.get(i));
        }
        return finalClusters;
    }

    // 주어진 하나의 클러스터에서 후보자들을 매칭시키는 함수
    private static List<List<Candidate>> matchWithinCluster(List<Candidate> cluster, Random rand) {
        List<List<Candidate>> matchedPairs = new ArrayList<>();
        // 후보자 리스트를 정렬 (예: rating 순)하거나 섞어서 순회
        Collections.sort(cluster); // rating 내림차순으로 정렬된 상태 (Comparable 구현에 따름)

        boolean[] matched = new boolean[cluster.size()]; // 매칭 여부 표시
        for (int i = 0; i < cluster.size(); i++) {
            if (matched[i])
                continue; // 이미 매칭된 경우 넘어감
            Candidate curr = cluster.get(i);
            // 이웃 후보 리스트 추출 (자기 자신 제외, 같은 클러스터 내)
            List<Candidate> neighbors = new ArrayList<>();
            for (int j = 0; j < cluster.size(); j++) {
                if (i == j || matched[j])
                    continue; // 자기 자신 또는 이미 매칭된 사람 제외
                neighbors.add(cluster.get(j));
            }
            if (neighbors.isEmpty()) {
                continue; // 이웃이 없으면 매칭 불가 (클러스터 내 남은 사람이 자기 자신뿐인 경우)
            }
            // 거리 기준으로 이웃들 정렬 후 상위 5명 선택
            neighbors.sort(Comparator.comparingDouble(c -> weightedDistance(curr, c)));
            int neighborCount = Math.min(CPD_CANDIDATE_COUNT, neighbors.size());
            List<Candidate> topNeighbors = neighbors.subList(0, neighborCount);

            // 가중치 합 계산 (유사도에 비례하는 가중치: 거리의 역수 활용)
            double totalWeight = 0.0;
            double[] weights = new double[neighborCount];
            for (int k = 0; k < neighborCount; k++) {
                double dist = weightedDistance(curr, topNeighbors.get(k));
                // 거리 -> 가중치 변환 (거리 0 대비 안전을 위해 아주 작은 값 추가)
                weights[k] = 1.0 / (dist + 1e-6);
                totalWeight += weights[k];
            }
            // 누적 확률 분포에 따라 무작위 선택, CPD 로직 : 148~158 line
            double r = rand.nextDouble() * totalWeight;
            double cumulative = 0.0;
            Candidate chosenNeighbor = null;
            for (int k = 0; k < neighborCount; k++) {
                cumulative += weights[k];
                if (r <= cumulative) {
                    chosenNeighbor = topNeighbors.get(k);
                    break;
                }
            }
            if (chosenNeighbor == null) {
                chosenNeighbor = topNeighbors.get(neighborCount - 1);
            }
            // 매칭된 쌍 기록
            matchedPairs.add(Arrays.asList(curr, chosenNeighbor));
            // 매칭된 두 후보자는 제외 처리
            matched[i] = true;
            // matched 배열에서 chosenNeighbor의 인덱스를 찾아서 표시
            for (int j = 0; j < cluster.size(); j++) {
                if (!matched[j] && cluster.get(j).equals(chosenNeighbor)) {
                    matched[j] = true;
                    break;
                }
            }
        }
        return matchedPairs;
    }

    public static void main(String[] args) {
        // 10명의 예제 후보자 생성 (id, rating, studyField, preferredTime)
        List<Candidate> candidates = new ArrayList<>();
        candidates.add(new Candidate(1, 9.0, 1, 1));
        candidates.add(new Candidate(2, 8.0, 1, 1));
        candidates.add(new Candidate(3, 5.0, 2, 0));
        candidates.add(new Candidate(4, 6.0, 2, 0));
        candidates.add(new Candidate(5, 4.0, 3, 2));
        candidates.add(new Candidate(6, 4.0, 3, 2));
        candidates.add(new Candidate(7, 7.0, 1, 1));
        candidates.add(new Candidate(8, 2.0, 2, 0));
        candidates.add(new Candidate(9, 10.0, 1, 1));
        candidates.add(new Candidate(10, 3.0, 3, 2));
        candidates.add(new Candidate(11, 7.5, 1, 1));
        candidates.add(new Candidate(12, 6.5, 2, 0));
        candidates.add(new Candidate(13, 5.5, 2, 0));
        candidates.add(new Candidate(14, 4.5, 3, 2));
        candidates.add(new Candidate(15, 8.5, 1, 1));
        candidates.add(new Candidate(16, 9.5, 1, 1));
        candidates.add(new Candidate(17, 3.5, 3, 2));
        candidates.add(new Candidate(18, 2.5, 2, 0));
        candidates.add(new Candidate(19, 7.8, 1, 1));
        candidates.add(new Candidate(20, 6.2, 2, 0));
        candidates.add(new Candidate(21, 4.8, 3, 2));
        candidates.add(new Candidate(22, 5.2, 2, 0));
        candidates.add(new Candidate(23, 8.2, 1, 1));
        candidates.add(new Candidate(24, 9.8, 1, 1));
        candidates.add(new Candidate(25, 3.8, 3, 2));
        candidates.add(new Candidate(26, 4.2, 3, 2));
        candidates.add(new Candidate(27, 6.8, 2, 0));
        candidates.add(new Candidate(28, 7.2, 1, 1));
        candidates.add(new Candidate(29, 5.8, 2, 0));

        // 후보자들을 클러스터링함. K=3으로 그룹화하므로 10 / 10 / 10
        List<List<Candidate>> clusters = clusterCandidates(candidates, CLUSTER_COUNT);

        // 각 클러스터 내부에서 매칭 수행
        Random rand = new Random(); // 난수 시드 고정 (실행 결과 재현 가능)
        List<List<Candidate>> allMatchedPairs = new ArrayList<>();
        for (List<Candidate> cluster : clusters) {
            List<List<Candidate>> pairs = matchWithinCluster(cluster, rand);
            allMatchedPairs.addAll(pairs);
        }

        // 결과 출력: 매칭된 쌍 나열
        System.out.println("Matched Pairs:");
        for (List<Candidate> pair : allMatchedPairs) {
            Candidate a = pair.get(0);
            Candidate b = pair.get(1);
            System.out.println("Candidate " + a.id + " - Candidate " + b.id);
        }
    }
}