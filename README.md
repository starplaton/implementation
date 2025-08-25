## Implementation Practice (C++ No-STL)

목표
- 다양한 문제를 직접 구현하며 C++ STL을 최소화/배제
- 저수준 자료구조/알고리즘 최적화 감각 향상
- 디버깅 루틴을 반복해 버그 탐지 능력 강화

디렉터리 구조
- `mk/`: 공용 Make 설정
- `lib/`: 공용 no-STL 베이스 라이브러리 (입출력, 메모리 유틸 등)
- `TEMPLATE/`: 문제 템플릿과 샘플 케이스
- `daily/`, `weekly/`: 날짜/주차별 문제 폴더
- `tools/`, `scripts/`: 생성/실행 스크립트
- `docs/`: 학습 노트, 회고

시작하기
1) 템플릿 복사로 새 문제 생성
2) `make run`으로 로컬 케이스 실행, `make judge`로 전체 케이스 확인
3) 구현 후 README에 접근/버그/교훈 기록

규칙 (허용 라이브러리/기능 화이트리스트)
- 컨테이너/알고리즘은 직접 구현 (STL 컨테이너/알고리즘 사용 금지)
- 허용 헤더: `<cstdio>`, `<iostream>`, `<cstdint>` 또는 `<stdint.h>`, 필요 시 `<cstring>`, `<cstdlib>`, `<cassert>`
- 금지: `<vector>`, `<string>`, `<algorithm>`, `<map>`, `<set>`, `<queue>`, `<stack>`, `<bitset>`, `<numeric>` 등 STL 컨테이너/알고리즘
- 동적 메모리: `malloc`/`free`(권장). `new`/`delete`는 제한적으로 허용
- 빠른 IO: `std::ios::sync_with_stdio(false); std::cin.tie(nullptr);` 또는 `lib/io.hpp`의 `fastio` 사용
- OS 헤더 `<unistd.h>`는 `lib/` 내부 구현에서만 사용 (문제 코드에서는 사용 금지)

예시 워크플로우(요약)
- 문제 생성 → 아이디어 스케치 → no-STL 자료구조 선택/구현 → 케이스 주도 디버깅 → 회고 기록

참고: 아래 Makefile/스크립트와 템플릿은 점진적으로 채워집니다.

사용법
- 새 문제 생성(일일):
  - `python3 tools/new_problem.py` → `daily/YYYY-MM-DD` 생성
- 특정 위치에 생성:
  - `python3 tools/new_problem.py weekly/week01/knapsack`
- 빌드/실행:
  - `make build PROB=daily/YYYY-MM-DD`
  - `make run PROB=daily/YYYY-MM-DD CASE=daily/YYYY-MM-DD/cases/1.in`
  - `make judge PROB=daily/YYYY-MM-DD`

검증 전용 알고리즘 세트
- 경로: `algorithms/{gcd,is_prime,sort,binary_search}`
- 각 폴더는 검증 케이스(`cases/`)만 제공하며, `main.cpp`는 비워둡니다(직접 구현).
- I/O 규격
  - gcd
    - 입력: 첫 줄 `T` (테스트 수), 다음 `T`줄에 정수 `a b`
    - 출력: 각 줄에 `gcd(a,b)` (음수 입력 시 결과는 비음수로 처리 권장)
  - is_prime
    - 입력: 첫 줄 `T`, 다음 `T`줄에 정수 `n`
    - 출력: 각 줄에 `YES` 또는 `NO` (대문자)
  - sort
    - 입력: 첫 줄 `n`, 둘째 줄에 `n`개의 정수
    - 출력: 한 줄에 오름차순 정렬 결과를 공백으로 구분해 출력
  - binary_search
    - 입력: 첫 줄 `n`, 둘째 줄 오름차순 정렬된 `n`개 정수, 셋째 줄 `q`, 넷째 줄 `q`개의 정수 쿼리
    - 출력: 각 쿼리에 대해 존재하면 `1`, 없으면 `0`

검증 방법
- 구현을 `algorithms/<name>/main.cpp`로 저장한 뒤 아래 실행
  - `make judge PROB=algorithms/<name>`
- 여러 알고리즘을 한 번에 검증
  - `scripts/verify_all.sh` 실행 시 `main.cpp`가 존재하는 폴더만 자동 검증합니다.

디버깅 규율(버그 찾기 능력 향상)
- 입력 최소반례 축소: 실패 케이스에서 입력을 최소화하며 원인 격리
- 가드 작성: 경계(0, 1, MAX, 음수)에 대한 분기 먼저 작성
- 로그 없이 추론: 입출력만으로 상태를 재현 가능한 형태로 함
- 불변식 점검 체크리스트 유지: 루프 전/후, 자료구조 상태