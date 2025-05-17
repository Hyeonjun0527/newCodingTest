package com.codezerotoone.mvp.domain.matching.batch.config;

import com.codezerotoone.mvp.domain.matching.entity.MatchingRequest;
import org.springframework.batch.core.Job;
import org.springframework.batch.core.Step;
import org.springframework.batch.core.job.builder.JobBuilder;
import org.springframework.batch.core.repository.JobRepository;
import org.springframework.batch.core.step.builder.StepBuilder;
import org.springframework.batch.item.ItemProcessor;
import org.springframework.batch.item.ItemReader;
import org.springframework.batch.item.ItemWriter;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import org.springframework.transaction.PlatformTransactionManager;

/**
 * 자동 매칭 Batch Job 및 Step 설정
 */
@Configuration
public class AutoMatchingJobConfig {

    public static final int CHUNK_SIZE = 10; // public static final로 변경

    @Bean
    public Job autoMatchingJob(JobRepository jobRepository, Step autoMatchingStep) {
        return new JobBuilder("autoMatchingJob", jobRepository)
                .start(autoMatchingStep)
                .build();
    }

    @Bean
    public Step autoMatchingStep(JobRepository jobRepository,
                                 PlatformTransactionManager transactionManager,
                                 ItemReader<MatchingRequest> autoMatchingItemReader,
                                 ItemProcessor<MatchingRequest, MatchingRequest> autoMatchingItemProcessor,
                                 ItemWriter<MatchingRequest> autoMatchingItemWriter) {
        return new StepBuilder("autoMatchingStep", jobRepository)
                .<MatchingRequest, MatchingRequest>chunk(CHUNK_SIZE, transactionManager)
                .reader(autoMatchingItemReader)
                .processor(autoMatchingItemProcessor)
                .writer(autoMatchingItemWriter)
                .faultTolerant()
                // .retryLimit(3).retry(Exception.class)
                // .skipLimit(10).skip(Exception.class)
                .build();
                
                
    }
} 