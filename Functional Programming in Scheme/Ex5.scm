
;;; Name: Caleb Shere
;;; Student ID: 2-49327691-9
;;; Tirgul Group: 89-310-05
;;; username: shereca
;;; Assignment 5

(define (starts-with prefix str)
  (define (list-starts-with ls1 ls2)
    (cond ((null? ls1) #t)
          ((null? ls2) #f)
          ((char=? (car ls1) (car ls2))
             (list-starts-with (cdr ls1) (cdr ls2)))
          (else #f)))
  (list-starts-with (string->list prefix) (string->list str)))

(define (sum-of-pairs-start-with prefix ls)
  (define (sum-help pre list sum)
    (cond ((null? list) sum)
          ((starts-with pre (car (car list)))
             (sum-help pre (cdr list) (+ sum (cdr (car list)))))
          (else (sum-help pre (cdr list) sum))))
  (sum-help prefix ls 0))

(define (zip ls1 ls2)
  (define (zip-help list1 list2 zipList)
    (if (or (null? list1) (null? list2))
        zipList
        (zip-help (cdr list1) (cdr list2) (append zipList (list (cons (car list1) (car list2)))))))
  (zip-help ls1 ls2 '()))

(define (rotate ls n)
  (define (sublist ls start end)
    (define (sublist-help ls start end subls index)
      (cond ((< index start) (sublist-help (cdr ls) start end subls (+ index 1)))
            ((> index end) subls)
            (else (sublist-help (cdr ls) start end (append subls (list (car ls))) (+ index 1)))))
    (sublist-help ls start end '() 0))
  (define (mod n k)
    (if (< n k)
       n
       (mod (- n k) k)))
  (if (= (length ls) 0)
      '()
      (let ((num (mod n (length ls)))
            (len (length ls))
            (last (- (length ls) 1)))
        (append (sublist ls (- len num) last) (sublist ls 0 (- last num))))))

(define (quicksort f)
  (define (quicksort-intern ls)
    (define (partition ls)
      (define (partition-help li pivot left-li right-li)
        (cond ((null? li) (list left-li pivot right-li))
              ((<= (f (car li) pivot) 0)
                 (partition-help (cdr li) pivot (append left-li (list (car li))) right-li))
              (else
                 (partition-help (cdr li) pivot left-li (append right-li (list (car li)))))))
      (partition-help (cdr ls) (car ls) '() '()))
    (define (quicksort-help li sorted-li)
      (if (<= (length li) 1)
          (append sorted-li li)
          (let ((parted-li (partition li)))
            (append sorted-li (append
                               (quicksort-help (car parted-li) sorted-li)
                               (append (list (cadr parted-li))
                                       (quicksort-help (caddr parted-li) sorted-li)))))))
    (quicksort-help ls '()))
  quicksort-intern)

(define (seq-gen u g)
  (cons u g))

(define (seq x)
  (seq-gen x (lambda (n) (+ n 1))))

(define (hd s)
  (car s))

(define (tail s)
  (seq-gen ((cdr s) (car s)) (cdr s)))

(define (cyclic-seq ls1)
  (define (find-next ls2 a)
    (if (eq? (car ls2) a)
        (if (null? (cdr ls2))
            (car ls1)
            (cadr ls2))
        (find-next (cdr ls2) a)))
    (define (func a)
      (find-next ls1 a))
  (seq-gen (car ls1) func))

(define (make-dictionary)
  (define (helper ls-of-pairs)
    (define (func arg)
      (define (find-value key li)
        (cond ((null? li) '())
              ((equal? (caar li) key) (cdar li))
              (else (find-value key (cdr li)))))
      (define (add-to-list pair li)
        (define (replace-pair p li)
          (define (replace-help p li new-li)
            (cond ((null? li) new-li)
                  ((equal? (car p) (caar li))
                     (replace-help p (cdr li) (append new-li (list p))))
                  (else (replace-help p (cdr li) (append new-li (list (car li)))))))
          (replace-help p li '()))
        (if (null? (find-value (car pair) li))
            (append li (list pair))
            (replace-pair pair li)))         
      (cond ((pair? arg) (helper (add-to-list arg ls-of-pairs)))
            ((null? arg) ls-of-pairs)
            (else (find-value arg ls-of-pairs))))
    func)
  (helper '()))

(define (most-common-word str)
  (define (helper li1 bigLi smallLi pair)
    (define (member small big)
      (cond ((null? big) #f)
            ((string=? (list->string small) (caar big)) #t)
            (else (member small (cdr big)))))
    (define (update-big-list big small pair)
      (define (update-help orig small pair new-li)
        (let ((currStr (list->string small)))
          (cond ((null? orig) (helper (cdr li1) new-li '() pair))
                ((string=? currStr (caar orig))
                   (let ((newPair (cons currStr (+ (cdar orig) 1))))
                     (if (> (cdr newPair) (cdr pair))
                         (update-help (cdr orig) small newPair (append new-li (list newPair)))
                         (update-help (cdr orig) small pair (append new-li (list newPair))))))
                (else (update-help (cdr orig) small pair (append new-li (list (car orig))))))))
      (update-help big small pair '()))
    (define (count-this-word bigLi smallLi pair)
      (if (member smallLi bigLi)
          (update-big-list bigLi smallLi pair)
          (if (null? bigLi)
              (helper (cdr li1) (list (cons (list->string smallLi) 1)) '() (cons (list->string smallLi) 1))
              (helper (cdr li1) (append bigLi (list (cons (list->string smallLi) 1))) '() pair))))
    (cond ((null? li1) pair)
          ((char=? (car li1) #\space) (count-this-word bigLi smallLi pair))
          (else (helper (cdr li1) bigLi (append smallLi (list (car li1))) pair))))
  (helper (append (string->list str) (list #\space)) '() '() (cons str 1)))

(load "test.scm")