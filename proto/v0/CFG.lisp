
;;;;    CFG.lisp

;;; Generated by the protocol buffer compiler.  DO NOT EDIT!


(cl:in-package #:common-lisp-user)
(eval-when (:compile-toplevel :load-toplevel :execute)
  (unless (find-package '#:proto-v0)
    (make-package '#:proto-v0 :use nil)))
(in-package #:proto-v0)
(cl:declaim #.com.google.base:*optimize-default*)

(cl:deftype edge-type () '(cl:member 0 1 2 3 4 5))
(cl:eval-when (:load-toplevel :compile-toplevel :execute)
  (cl:export 'edge-type))

(cl:defconstant +edge-type-type-branch+ 0)
(cl:eval-when (:load-toplevel :compile-toplevel :execute)
  (cl:export '+edge-type-type-branch+))
(cl:defconstant +edge-type-type-call+ 1)
(cl:eval-when (:load-toplevel :compile-toplevel :execute)
  (cl:export '+edge-type-type-call+))
(cl:defconstant +edge-type-type-fallthrough+ 2)
(cl:eval-when (:load-toplevel :compile-toplevel :execute)
  (cl:export '+edge-type-type-fallthrough+))
(cl:defconstant +edge-type-type-return+ 3)
(cl:eval-when (:load-toplevel :compile-toplevel :execute)
  (cl:export '+edge-type-type-return+))
(cl:defconstant +edge-type-type-syscall+ 4)
(cl:eval-when (:load-toplevel :compile-toplevel :execute)
  (cl:export '+edge-type-type-syscall+))
(cl:defconstant +edge-type-type-sysret+ 5)
(cl:eval-when (:load-toplevel :compile-toplevel :execute)
  (cl:export '+edge-type-type-sysret+))

(cl:defconstant +minimum-edge-type+ +edge-type-type-branch+)
(cl:eval-when (:load-toplevel :compile-toplevel :execute)
  (cl:export '+minimum-edge-type+))
(cl:defconstant +maximum-edge-type+ +edge-type-type-sysret+)
(cl:eval-when (:load-toplevel :compile-toplevel :execute)
  (cl:export '+maximum-edge-type+))

(cl:defclass edge-label (pb:protocol-buffer)
  (
  (conditional
   :accessor conditional
   :initarg :conditional
   :initform cl:nil
   :type cl:boolean)
  (direct
   :accessor direct
   :initarg :direct
   :initform cl:nil
   :type cl:boolean)
  (type
   :accessor type
   :initarg :type
   :initform proto-v0::+edge-type-type-branch+
   :type proto-v0::edge-type)
  (%has-bits%
   :accessor %has-bits%
   :initform 0
   :type (cl:unsigned-byte 3))
  (pb::%cached-size%
   :initform 0
   :type (cl:integer 0 #.(cl:1- cl:array-dimension-limit)))
  ))

(cl:defmethod cl:initialize-instance :after
  ((self edge-label) cl:&key
                  (conditional cl:nil conditional-p)
                  (direct cl:nil direct-p)
                  (type cl:nil type-p)
                  )
  (cl:declare (cl:ignore conditional direct type))
  (cl:when conditional-p
    (cl:setf (cl:ldb (cl:byte 1 0) (cl:slot-value self '%has-bits%)) 1))
  (cl:when direct-p
    (cl:setf (cl:ldb (cl:byte 1 1) (cl:slot-value self '%has-bits%)) 1))
  (cl:when type-p
    (cl:setf (cl:ldb (cl:byte 1 2) (cl:slot-value self '%has-bits%)) 1))
  )

(cl:eval-when (:load-toplevel :compile-toplevel :execute)
  (cl:export 'edge-label))

(cl:eval-when (:load-toplevel :compile-toplevel :execute)
  (cl:export 'conditional))


(cl:defmethod (cl:setf conditional) :after (x (self edge-label))
  (cl:declare (cl:ignore x))
  (cl:setf (cl:ldb (cl:byte 1 0) (cl:slot-value self '%has-bits%)) 1))

(cl:unless (cl:fboundp 'has-conditional)
  (cl:defgeneric has-conditional (proto)))
(cl:defmethod has-conditional ((self edge-label))
  (cl:logbitp 0 (cl:slot-value self '%has-bits%)))
(cl:eval-when (:load-toplevel :compile-toplevel :execute)
  (cl:export 'has-conditional))

(cl:unless (cl:fboundp 'clear-conditional)
  (cl:defgeneric clear-conditional (proto)))
(cl:defmethod clear-conditional ((self edge-label))
  (cl:setf (cl:slot-value self 'conditional) cl:nil)
  (cl:setf (cl:ldb (cl:byte 1 0) (cl:slot-value self '%has-bits%)) 0)
  (cl:values))
(cl:eval-when (:load-toplevel :compile-toplevel :execute)
  (cl:export 'clear-conditional))

(cl:eval-when (:load-toplevel :compile-toplevel :execute)
  (cl:export 'direct))


(cl:defmethod (cl:setf direct) :after (x (self edge-label))
  (cl:declare (cl:ignore x))
  (cl:setf (cl:ldb (cl:byte 1 1) (cl:slot-value self '%has-bits%)) 1))

(cl:unless (cl:fboundp 'has-direct)
  (cl:defgeneric has-direct (proto)))
(cl:defmethod has-direct ((self edge-label))
  (cl:logbitp 1 (cl:slot-value self '%has-bits%)))
(cl:eval-when (:load-toplevel :compile-toplevel :execute)
  (cl:export 'has-direct))

(cl:unless (cl:fboundp 'clear-direct)
  (cl:defgeneric clear-direct (proto)))
(cl:defmethod clear-direct ((self edge-label))
  (cl:setf (cl:slot-value self 'direct) cl:nil)
  (cl:setf (cl:ldb (cl:byte 1 1) (cl:slot-value self '%has-bits%)) 0)
  (cl:values))
(cl:eval-when (:load-toplevel :compile-toplevel :execute)
  (cl:export 'clear-direct))

(cl:eval-when (:load-toplevel :compile-toplevel :execute)
  (cl:export 'type))


(cl:defmethod (cl:setf type) :after (x (self edge-label))
  (cl:declare (cl:ignore x))
  (cl:setf (cl:ldb (cl:byte 1 2) (cl:slot-value self '%has-bits%)) 1))

(cl:unless (cl:fboundp 'has-type)
  (cl:defgeneric has-type (proto)))
(cl:defmethod has-type ((self edge-label))
  (cl:logbitp 2 (cl:slot-value self '%has-bits%)))
(cl:eval-when (:load-toplevel :compile-toplevel :execute)
  (cl:export 'has-type))

(cl:unless (cl:fboundp 'clear-type)
  (cl:defgeneric clear-type (proto)))
(cl:defmethod clear-type ((self edge-label))
  (cl:setf (cl:slot-value self 'type) proto-v0::+edge-type-type-branch+)
  (cl:setf (cl:ldb (cl:byte 1 2) (cl:slot-value self '%has-bits%)) 0)
  (cl:values))
(cl:eval-when (:load-toplevel :compile-toplevel :execute)
  (cl:export 'clear-type))


(cl:defmethod cl:print-object ((self edge-label) stream)
  (cl:pprint-logical-block (stream cl:nil)
    (cl:print-unreadable-object (self stream :type cl:t :identity cl:t)
      (cl:when (cl:logbitp 0 (cl:slot-value self '%has-bits%))
        (cl:format stream " ~_conditional: ~s" (conditional self)))
      (cl:when (cl:logbitp 1 (cl:slot-value self '%has-bits%))
        (cl:format stream " ~_direct: ~s" (direct self)))
      (cl:when (cl:logbitp 2 (cl:slot-value self '%has-bits%))
        (cl:format stream " ~_type: ~s" (type self)))
      ))
  (cl:values))

(cl:defmethod pb:clear ((self edge-label))
  (cl:setf (cl:slot-value self 'conditional) cl:nil)
  (cl:setf (cl:slot-value self 'direct) cl:nil)
  (cl:setf (cl:slot-value self 'type) proto-v0::+edge-type-type-branch+)
  (cl:setf (cl:slot-value self '%has-bits%) 0)
  (cl:values))

(cl:defmethod pb:is-initialized ((self edge-label))
  cl:t)

(cl:defmethod pb:octet-size ((self edge-label))
  (cl:let ((size 0))
    ;; bool conditional = 1[json_name = "conditional"];
    (cl:when (cl:logbitp 0 (cl:slot-value self '%has-bits%))
      (cl:incf size
        (cl:+ 1 1)))
    ;; bool direct = 2[json_name = "direct"];
    (cl:when (cl:logbitp 1 (cl:slot-value self '%has-bits%))
      (cl:incf size
        (cl:+ 1 1)))
    ;; .protoV0.EdgeType type = 3[json_name = "type"];
    (cl:when (cl:logbitp 2 (cl:slot-value self '%has-bits%))
      (cl:incf size 1)
      (cl:incf size (varint:length64 (cl:ldb (cl:byte 64 0) (cl:slot-value self 'type)))))
    (cl:setf (cl:slot-value self 'pb::%cached-size%) size)
    size))

(cl:defmethod pb:serialize ((self edge-label) buffer index limit)
  (cl:declare (cl:type com.google.base:octet-vector buffer)
              (cl:type com.google.base:vector-index index limit)
              (cl:ignorable buffer limit))
  ;; bool conditional = 1[json_name = "conditional"];
  (cl:when (cl:logbitp 0 (cl:slot-value self '%has-bits%))
    (cl:setf index (varint:encode-uint32-carefully buffer index limit 8))
    (cl:setf index (wire-format:write-boolean-carefully buffer index limit (cl:slot-value self 'conditional))))
  ;; bool direct = 2[json_name = "direct"];
  (cl:when (cl:logbitp 1 (cl:slot-value self '%has-bits%))
    (cl:setf index (varint:encode-uint32-carefully buffer index limit 16))
    (cl:setf index (wire-format:write-boolean-carefully buffer index limit (cl:slot-value self 'direct))))
  ;; .protoV0.EdgeType type = 3[json_name = "type"];
  (cl:when (cl:logbitp 2 (cl:slot-value self '%has-bits%))
    (cl:setf index (varint:encode-uint32-carefully buffer index limit 24))
    (cl:setf index
     (varint:encode-uint64-carefully buffer index limit
      (cl:ldb (cl:byte 64 0) (cl:slot-value self 'type)))))
  index)

(cl:defmethod pb:merge-from-array ((self edge-label) buffer start limit)
  (cl:declare (cl:type com.google.base:octet-vector buffer)
              (cl:type com.google.base:vector-index start limit))
  (cl:do ((index start index))
      ((cl:>= index limit) index)
    (cl:declare (cl:type com.google.base:vector-index index))
    (cl:multiple-value-bind (tag new-index)
        (varint:parse-uint32-carefully buffer index limit)
      (cl:setf index new-index)
      (cl:case tag
        ;; bool conditional = 1[json_name = "conditional"];
        ((8)
          (cl:multiple-value-bind (value new-index)
              (wire-format:read-boolean-carefully buffer index limit)
            (cl:setf (cl:slot-value self 'conditional) value)
            (cl:setf (cl:ldb (cl:byte 1 0) (cl:slot-value self '%has-bits%)) 1)
            (cl:setf index new-index)))
        ;; bool direct = 2[json_name = "direct"];
        ((16)
          (cl:multiple-value-bind (value new-index)
              (wire-format:read-boolean-carefully buffer index limit)
            (cl:setf (cl:slot-value self 'direct) value)
            (cl:setf (cl:ldb (cl:byte 1 1) (cl:slot-value self '%has-bits%)) 1)
            (cl:setf index new-index)))
        ;; .protoV0.EdgeType type = 3[json_name = "type"];
        ((24)
          (cl:multiple-value-bind (value new-index)
              (varint:parse-int32-carefully buffer index limit)
            ;; XXXXX: when valid, set field, else add to unknown fields
            (cl:setf (cl:slot-value self 'type) value)
            (cl:setf (cl:ldb (cl:byte 1 2) (cl:slot-value self '%has-bits%)) 1)
            (cl:setf index new-index)))
        (cl:t
          (cl:when (cl:= (cl:logand tag 7) 4)
            (cl:return-from pb:merge-from-array index))
          (cl:setf index (wire-format:skip-field buffer index limit tag)))))))

(cl:defmethod pb:merge-from-message ((self edge-label) (from edge-label))
  (cl:when (cl:logbitp 0 (cl:slot-value from '%has-bits%))
    (cl:setf (cl:slot-value self 'conditional) (cl:slot-value from 'conditional))
    (cl:setf (cl:ldb (cl:byte 1 0) (cl:slot-value self '%has-bits%)) 1))
  (cl:when (cl:logbitp 1 (cl:slot-value from '%has-bits%))
    (cl:setf (cl:slot-value self 'direct) (cl:slot-value from 'direct))
    (cl:setf (cl:ldb (cl:byte 1 1) (cl:slot-value self '%has-bits%)) 1))
  (cl:when (cl:logbitp 2 (cl:slot-value from '%has-bits%))
    (cl:setf (cl:slot-value self 'type) (cl:slot-value from 'type))
    (cl:setf (cl:ldb (cl:byte 1 2) (cl:slot-value self '%has-bits%)) 1))
)


(cl:defclass edge (pb:protocol-buffer)
  (
  (source-uuid
   :accessor source-uuid
   :initarg :source-uuid
   :initform (cl:make-array 0 :element-type '(cl:unsigned-byte 8))
   :type (cl:simple-array (cl:unsigned-byte 8) (cl:*)))
  (target-uuid
   :accessor target-uuid
   :initarg :target-uuid
   :initform (cl:make-array 0 :element-type '(cl:unsigned-byte 8))
   :type (cl:simple-array (cl:unsigned-byte 8) (cl:*)))
  (label
   :writer (cl:setf label)
   :initarg :label
   :initform cl:nil
   :type (cl:or cl:null proto-v0::edge-label))
  (%has-bits%
   :accessor %has-bits%
   :initform 0
   :type (cl:unsigned-byte 3))
  (pb::%cached-size%
   :initform 0
   :type (cl:integer 0 #.(cl:1- cl:array-dimension-limit)))
  ))

(cl:defmethod cl:initialize-instance :after
  ((self edge) cl:&key
                  (source-uuid cl:nil source-uuid-p)
                  (target-uuid cl:nil target-uuid-p)
                  (label cl:nil label-p)
                  )
  (cl:declare (cl:ignore source-uuid target-uuid label))
  (cl:when source-uuid-p
    (cl:setf (cl:ldb (cl:byte 1 0) (cl:slot-value self '%has-bits%)) 1))
  (cl:when target-uuid-p
    (cl:setf (cl:ldb (cl:byte 1 1) (cl:slot-value self '%has-bits%)) 1))
  (cl:when label-p
    (cl:setf (cl:ldb (cl:byte 1 2) (cl:slot-value self '%has-bits%)) 1))
  )

(cl:eval-when (:load-toplevel :compile-toplevel :execute)
  (cl:export 'edge))

(cl:eval-when (:load-toplevel :compile-toplevel :execute)
  (cl:export 'source-uuid))


(cl:defmethod (cl:setf source-uuid) :after (x (self edge))
  (cl:declare (cl:ignore x))
  (cl:setf (cl:ldb (cl:byte 1 0) (cl:slot-value self '%has-bits%)) 1))

(cl:unless (cl:fboundp 'has-source-uuid)
  (cl:defgeneric has-source-uuid (proto)))
(cl:defmethod has-source-uuid ((self edge))
  (cl:logbitp 0 (cl:slot-value self '%has-bits%)))
(cl:eval-when (:load-toplevel :compile-toplevel :execute)
  (cl:export 'has-source-uuid))

(cl:unless (cl:fboundp 'clear-source-uuid)
  (cl:defgeneric clear-source-uuid (proto)))
(cl:defmethod clear-source-uuid ((self edge))
  (cl:setf (cl:slot-value self 'source-uuid) (cl:make-array 0 :element-type '(cl:unsigned-byte 8)))
  (cl:setf (cl:ldb (cl:byte 1 0) (cl:slot-value self '%has-bits%)) 0)
  (cl:values))
(cl:eval-when (:load-toplevel :compile-toplevel :execute)
  (cl:export 'clear-source-uuid))

(cl:eval-when (:load-toplevel :compile-toplevel :execute)
  (cl:export 'target-uuid))


(cl:defmethod (cl:setf target-uuid) :after (x (self edge))
  (cl:declare (cl:ignore x))
  (cl:setf (cl:ldb (cl:byte 1 1) (cl:slot-value self '%has-bits%)) 1))

(cl:unless (cl:fboundp 'has-target-uuid)
  (cl:defgeneric has-target-uuid (proto)))
(cl:defmethod has-target-uuid ((self edge))
  (cl:logbitp 1 (cl:slot-value self '%has-bits%)))
(cl:eval-when (:load-toplevel :compile-toplevel :execute)
  (cl:export 'has-target-uuid))

(cl:unless (cl:fboundp 'clear-target-uuid)
  (cl:defgeneric clear-target-uuid (proto)))
(cl:defmethod clear-target-uuid ((self edge))
  (cl:setf (cl:slot-value self 'target-uuid) (cl:make-array 0 :element-type '(cl:unsigned-byte 8)))
  (cl:setf (cl:ldb (cl:byte 1 1) (cl:slot-value self '%has-bits%)) 0)
  (cl:values))
(cl:eval-when (:load-toplevel :compile-toplevel :execute)
  (cl:export 'clear-target-uuid))

(cl:eval-when (:load-toplevel :compile-toplevel :execute)
  (cl:export 'label))

(cl:unless (cl:fboundp 'label)
  (cl:defgeneric label (proto)))
(cl:defmethod label ((self edge))
  (cl:let ((result (cl:slot-value self 'label)))
    (cl:when (cl:null result)
      (cl:setf result (cl:make-instance 'proto-v0::edge-label))
      (cl:setf (cl:slot-value self 'label) result))
      (cl:setf (cl:ldb (cl:byte 1 2) (cl:slot-value self '%has-bits%)) 1)
    result))

(cl:defmethod (cl:setf label) :after (x (self edge))
  (cl:declare (cl:ignore x))
  (cl:setf (cl:ldb (cl:byte 1 2) (cl:slot-value self '%has-bits%)) 1))

(cl:unless (cl:fboundp 'has-label)
  (cl:defgeneric has-label (proto)))
(cl:defmethod has-label ((self edge))
  (cl:logbitp 2 (cl:slot-value self '%has-bits%)))
(cl:eval-when (:load-toplevel :compile-toplevel :execute)
  (cl:export 'has-label))

(cl:unless (cl:fboundp 'clear-label)
  (cl:defgeneric clear-label (proto)))
(cl:defmethod clear-label ((self edge))
  (cl:setf (cl:slot-value self 'label) cl:nil)
  (cl:setf (cl:ldb (cl:byte 1 2) (cl:slot-value self '%has-bits%)) 0)
  (cl:values))
(cl:eval-when (:load-toplevel :compile-toplevel :execute)
  (cl:export 'clear-label))


(cl:defmethod cl:print-object ((self edge) stream)
  (cl:pprint-logical-block (stream cl:nil)
    (cl:print-unreadable-object (self stream :type cl:t :identity cl:t)
      (cl:when (cl:logbitp 0 (cl:slot-value self '%has-bits%))
        (cl:format stream " ~_source-uuid: ~s" (source-uuid self)))
      (cl:when (cl:logbitp 1 (cl:slot-value self '%has-bits%))
        (cl:format stream " ~_target-uuid: ~s" (target-uuid self)))
      (cl:when (cl:logbitp 2 (cl:slot-value self '%has-bits%))
        (cl:format stream " ~_label: ~s" (label self)))
      ))
  (cl:values))

(cl:defmethod pb:clear ((self edge))
  (cl:when (cl:logbitp 0 (cl:slot-value self '%has-bits%))
    (cl:setf (cl:slot-value self 'source-uuid) (cl:make-array 0 :element-type '(cl:unsigned-byte 8))))
  (cl:when (cl:logbitp 1 (cl:slot-value self '%has-bits%))
    (cl:setf (cl:slot-value self 'target-uuid) (cl:make-array 0 :element-type '(cl:unsigned-byte 8))))
  (cl:when (cl:logbitp 2 (cl:slot-value self '%has-bits%))
    (cl:setf (cl:slot-value self 'label) cl:nil))
  (cl:setf (cl:slot-value self '%has-bits%) 0)
  (cl:values))

(cl:defmethod pb:is-initialized ((self edge))
  cl:t)

(cl:defmethod pb:octet-size ((self edge))
  (cl:let ((size 0))
    ;; bytes source_uuid = 1[json_name = "sourceUuid"];
    (cl:when (cl:logbitp 0 (cl:slot-value self '%has-bits%))
      (cl:incf size 1)
      (cl:incf size (cl:let ((s (cl:length (cl:slot-value self 'source-uuid))))
        (cl:+ s (varint:length32 s)))))
    ;; bytes target_uuid = 2[json_name = "targetUuid"];
    (cl:when (cl:logbitp 1 (cl:slot-value self '%has-bits%))
      (cl:incf size 1)
      (cl:incf size (cl:let ((s (cl:length (cl:slot-value self 'target-uuid))))
        (cl:+ s (varint:length32 s)))))
    ;; .protoV0.EdgeLabel label = 5[json_name = "label"];
    (cl:when (cl:logbitp 2 (cl:slot-value self '%has-bits%))
      (cl:let ((s (pb:octet-size (cl:slot-value self 'label))))
        (cl:incf size (cl:+ 1 s (varint:length32 s)))))
    (cl:setf (cl:slot-value self 'pb::%cached-size%) size)
    size))

(cl:defmethod pb:serialize ((self edge) buffer index limit)
  (cl:declare (cl:type com.google.base:octet-vector buffer)
              (cl:type com.google.base:vector-index index limit)
              (cl:ignorable buffer limit))
  ;; bytes source_uuid = 1[json_name = "sourceUuid"];
  (cl:when (cl:logbitp 0 (cl:slot-value self '%has-bits%))
    (cl:setf index (varint:encode-uint32-carefully buffer index limit 10))
    (cl:setf index (wire-format:write-octets-carefully buffer index limit (cl:slot-value self 'source-uuid))))
  ;; bytes target_uuid = 2[json_name = "targetUuid"];
  (cl:when (cl:logbitp 1 (cl:slot-value self '%has-bits%))
    (cl:setf index (varint:encode-uint32-carefully buffer index limit 18))
    (cl:setf index (wire-format:write-octets-carefully buffer index limit (cl:slot-value self 'target-uuid))))
  ;; .protoV0.EdgeLabel label = 5[json_name = "label"];
  (cl:when (cl:logbitp 2 (cl:slot-value self '%has-bits%))
    (cl:setf index (varint:encode-uint32-carefully buffer index limit 42))
    (cl:setf index (varint:encode-uint32-carefully buffer index limit (cl:slot-value (cl:slot-value self 'label) 'pb::%cached-size%)))
    (cl:setf index (pb:serialize (cl:slot-value self 'label) buffer index limit)))
  index)

(cl:defmethod pb:merge-from-array ((self edge) buffer start limit)
  (cl:declare (cl:type com.google.base:octet-vector buffer)
              (cl:type com.google.base:vector-index start limit))
  (cl:do ((index start index))
      ((cl:>= index limit) index)
    (cl:declare (cl:type com.google.base:vector-index index))
    (cl:multiple-value-bind (tag new-index)
        (varint:parse-uint32-carefully buffer index limit)
      (cl:setf index new-index)
      (cl:case tag
        ;; bytes source_uuid = 1[json_name = "sourceUuid"];
        ((10)
          (cl:multiple-value-bind (value new-index)
              (wire-format:read-octets-carefully buffer index limit)
            (cl:setf (cl:slot-value self 'source-uuid) value)
            (cl:setf (cl:ldb (cl:byte 1 0) (cl:slot-value self '%has-bits%)) 1)
            (cl:setf index new-index)))
        ;; bytes target_uuid = 2[json_name = "targetUuid"];
        ((18)
          (cl:multiple-value-bind (value new-index)
              (wire-format:read-octets-carefully buffer index limit)
            (cl:setf (cl:slot-value self 'target-uuid) value)
            (cl:setf (cl:ldb (cl:byte 1 1) (cl:slot-value self '%has-bits%)) 1)
            (cl:setf index new-index)))
        ;; .protoV0.EdgeLabel label = 5[json_name = "label"];
        ((42)
          (cl:multiple-value-bind (length new-index)
              (varint:parse-uint31-carefully buffer index limit)
            (cl:when (cl:> (cl:+ new-index length) limit)
              (cl:error "buffer overflow"))
            (cl:let ((message (cl:slot-value self 'label)))
              (cl:when (cl:null message)
                (cl:setf message (cl:make-instance 'proto-v0::edge-label))
                (cl:setf (cl:slot-value self 'label) message)
                (cl:setf (cl:ldb (cl:byte 1 2) (cl:slot-value self '%has-bits%)) 1))
              (cl:setf index (pb:merge-from-array message buffer new-index (cl:+ new-index length)))
              (cl:when (cl:not (cl:= index (cl:+ new-index length)))
                (cl:error "buffer overflow")))))
        (cl:t
          (cl:when (cl:= (cl:logand tag 7) 4)
            (cl:return-from pb:merge-from-array index))
          (cl:setf index (wire-format:skip-field buffer index limit tag)))))))

(cl:defmethod pb:merge-from-message ((self edge) (from edge))
  (cl:when (cl:logbitp 0 (cl:slot-value from '%has-bits%))
    (cl:setf (cl:slot-value self 'source-uuid) (cl:slot-value from 'source-uuid))
    (cl:setf (cl:ldb (cl:byte 1 0) (cl:slot-value self '%has-bits%)) 1))
  (cl:when (cl:logbitp 1 (cl:slot-value from '%has-bits%))
    (cl:setf (cl:slot-value self 'target-uuid) (cl:slot-value from 'target-uuid))
    (cl:setf (cl:ldb (cl:byte 1 1) (cl:slot-value self '%has-bits%)) 1))
  (cl:when (cl:logbitp 2 (cl:slot-value from '%has-bits%))
    (cl:let ((message (cl:slot-value self 'label)))
      (cl:when (cl:null message)
        (cl:setf message (cl:make-instance 'proto-v0::edge-label))
        (cl:setf (cl:slot-value self 'label) message)
        (cl:setf (cl:ldb (cl:byte 1 2) (cl:slot-value self '%has-bits%)) 1))
     (pb:merge-from-message message (cl:slot-value from 'label))))
)


(cl:defclass cfg (pb:protocol-buffer)
  (
  (vertices
   :accessor vertices
   :initarg :vertices
   :initform (cl:make-array
              0
              :element-type '(cl:simple-array (cl:unsigned-byte 8) (cl:*))
              :fill-pointer 0 :adjustable cl:t)
   :type (cl:vector (cl:simple-array (cl:unsigned-byte 8) (cl:*))))
  (edges
   :accessor edges
   :initarg :edges
   :initform (cl:make-array
              0
              :element-type 'proto-v0::edge
              :fill-pointer 0 :adjustable cl:t)
   :type (cl:vector proto-v0::edge))
  (%has-bits%
   :accessor %has-bits%
   :initform 0
   :type (cl:unsigned-byte 2))
  (pb::%cached-size%
   :initform 0
   :type (cl:integer 0 #.(cl:1- cl:array-dimension-limit)))
  ))

(cl:defmethod cl:initialize-instance :after
  ((self cfg) cl:&key
                  (vertices cl:nil vertices-p)
                  (edges cl:nil edges-p)
                  )
  (cl:declare (cl:ignore vertices edges))
  (cl:when vertices-p
    (cl:setf (cl:ldb (cl:byte 1 0) (cl:slot-value self '%has-bits%)) 1))
  (cl:when edges-p
    (cl:setf (cl:ldb (cl:byte 1 1) (cl:slot-value self '%has-bits%)) 1))
  )

(cl:eval-when (:load-toplevel :compile-toplevel :execute)
  (cl:export 'cfg))

(cl:eval-when (:load-toplevel :compile-toplevel :execute)
  (cl:export 'vertices))

(cl:unless (cl:fboundp 'clear-vertices)
  (cl:defgeneric clear-vertices (proto)))
(cl:defmethod clear-vertices ((self cfg))
  (cl:setf (cl:slot-value self 'vertices)
           (cl:make-array
            0
            :element-type '(cl:simple-array (cl:unsigned-byte 8) (cl:*))
            :fill-pointer 0 :adjustable cl:t))
  (cl:values))
(cl:eval-when (:load-toplevel :compile-toplevel :execute)
  (cl:export 'clear-vertices))

(cl:eval-when (:load-toplevel :compile-toplevel :execute)
  (cl:export 'edges))

(cl:unless (cl:fboundp 'clear-edges)
  (cl:defgeneric clear-edges (proto)))
(cl:defmethod clear-edges ((self cfg))
  (cl:setf (cl:slot-value self 'edges)
           (cl:make-array 0 :element-type 'proto-v0::edge
            :fill-pointer 0 :adjustable cl:t))
  (cl:values))
(cl:eval-when (:load-toplevel :compile-toplevel :execute)
  (cl:export 'clear-edges))


(cl:defmethod cl:print-object ((self cfg) stream)
  (cl:pprint-logical-block (stream cl:nil)
    (cl:print-unreadable-object (self stream :type cl:t :identity cl:t)
      (cl:format stream " ~_vertices: ~s" (vertices self))
      (cl:format stream " ~_edges: ~s" (edges self))
      ))
  (cl:values))

(cl:defmethod pb:clear ((self cfg))
  (cl:setf (cl:slot-value self 'vertices)
           (cl:make-array
            0
            :element-type '(cl:simple-array (cl:unsigned-byte 8) (cl:*))
            :fill-pointer 0 :adjustable cl:t))
  (cl:setf (cl:slot-value self 'edges)
           (cl:make-array 0 :element-type 'proto-v0::edge
            :fill-pointer 0 :adjustable cl:t))
  (cl:setf (cl:slot-value self '%has-bits%) 0)
  (cl:values))

(cl:defmethod pb:is-initialized ((self cfg))
  cl:t)

(cl:defmethod pb:octet-size ((self cfg))
  (cl:let ((size 0))
    ;; repeated bytes vertices = 3[json_name = "vertices"];
    (cl:let* ((x (cl:slot-value self 'vertices))
              (length (cl:length x)))
      (cl:incf size (cl:* 1 length))
      (cl:dotimes (i length)
        (cl:incf size (cl:let ((s (cl:length (cl:aref x i))))
  (cl:+ s (varint:length32 s))))))
    ;; repeated .protoV0.Edge edges = 2[json_name = "edges"];
    (cl:let* ((v (cl:slot-value self 'edges))
              (length (cl:length v)))
      (cl:incf size (cl:* 1 length))
      (cl:dotimes (i length)
        (cl:let ((s (pb:octet-size (cl:aref v i))))
          (cl:incf size (cl:+ s (varint:length32 s))))))
    (cl:setf (cl:slot-value self 'pb::%cached-size%) size)
    size))

(cl:defmethod pb:serialize ((self cfg) buffer index limit)
  (cl:declare (cl:type com.google.base:octet-vector buffer)
              (cl:type com.google.base:vector-index index limit)
              (cl:ignorable buffer limit))
  ;; repeated .protoV0.Edge edges = 2[json_name = "edges"];
  (cl:let* ((v (cl:slot-value self 'edges))
            (length (cl:length v)))
    (cl:loop for i from 0 below length do
       (cl:setf index (varint:encode-uint32-carefully buffer index limit 18))
       (cl:setf index (varint:encode-uint32-carefully buffer index limit (cl:slot-value (cl:aref v i) 'pb::%cached-size%)))
       (cl:setf index (pb:serialize (cl:aref v i) buffer index limit))))
  ;; repeated bytes vertices = 3[json_name = "vertices"];
  (cl:let* ((v (cl:slot-value self 'vertices))
            (length (cl:length v)))
    (cl:dotimes (i length)
      (cl:setf index (varint:encode-uint32-carefully buffer index limit 26))
      (cl:setf index (wire-format:write-octets-carefully buffer index limit (cl:aref v i)))))
  index)

(cl:defmethod pb:merge-from-array ((self cfg) buffer start limit)
  (cl:declare (cl:type com.google.base:octet-vector buffer)
              (cl:type com.google.base:vector-index start limit))
  (cl:do ((index start index))
      ((cl:>= index limit) index)
    (cl:declare (cl:type com.google.base:vector-index index))
    (cl:multiple-value-bind (tag new-index)
        (varint:parse-uint32-carefully buffer index limit)
      (cl:setf index new-index)
      (cl:case tag
        ;; repeated .protoV0.Edge edges = 2[json_name = "edges"];
        ((18)
          (cl:multiple-value-bind (length new-index)
              (varint:parse-uint31-carefully buffer index limit)
            (cl:when (cl:> (cl:+ new-index length) limit)
              (cl:error "buffer overflow"))
            (cl:let ((message (cl:make-instance 'proto-v0::edge)))
              (cl:setf index (pb:merge-from-array message buffer new-index (cl:+ new-index length)))
              (cl:when (cl:not (cl:= index (cl:+ new-index length)))
                (cl:error "buffer overflow"))
              (cl:vector-push-extend message (cl:slot-value self 'edges)))))
        ;; repeated bytes vertices = 3[json_name = "vertices"];
        ((26)
          (cl:multiple-value-bind (value new-index)
              (wire-format:read-octets-carefully buffer index limit)
            (cl:vector-push-extend value (cl:slot-value self 'vertices))
            (cl:setf index new-index)))
        (cl:t
          (cl:when (cl:= (cl:logand tag 7) 4)
            (cl:return-from pb:merge-from-array index))
          (cl:setf index (wire-format:skip-field buffer index limit tag)))))))

(cl:defmethod pb:merge-from-message ((self cfg) (from cfg))
  (cl:let ((v (cl:slot-value self 'vertices))
           (vf (cl:slot-value from 'vertices)))
    (cl:dotimes (i (cl:length vf))
      (cl:vector-push-extend (cl:aref vf i) v)))
  (cl:let* ((v (cl:slot-value self 'edges))
            (vf (cl:slot-value from 'edges))
            (length (cl:length vf)))
    (cl:loop for i from 0 below length do
      (cl:vector-push-extend (cl:aref vf i) v)))
)


